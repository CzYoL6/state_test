using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager_ShooterTest : Singleton<GameManager_ShooterTest>
{
    public int tickNum;
    public LocalPlayer_ShooterTest localPlayer;
    public int localPlayerID;

    public bool started = false;

    public Dictionary<int, Player_ShooterTest> playerMap;

    public Queue<UpdateShooterTest.UpdateInfo_S_TO_C> updates;

    public List<UpdateShooterTest.UpdateInfo_S_TO_C> interpList; //size = interp_ratio + 1
    public int interpRatio;


    public GameObject playerPrefab;

    public bool prediction, reconciliation, compensation, interpolation;

    [HideInInspector]public float tickRate;

    public float maxDiffPos , maxDiffRot;

    private float lastTickTime;

    public void StartGame() {
        tickRate = InfoKeeper.Instance.tickRate;
        started = true;
        playerMap = new Dictionary<int, Player_ShooterTest>();
        updates = new Queue<UpdateShooterTest.UpdateInfo_S_TO_C>();
        interpList = new List<UpdateShooterTest.UpdateInfo_S_TO_C>();
        lastTickTime = 0.0f;
        tickNum = 0;
    }
    private void FixedUpdate() {
        

    }

    private void Update() {
        NetManager.Instance.Tick();
        float curTime = Time.time;
        //Debug.Log(1.0f/tickRate);

        //Debug.Log("interp List size: " + interpList.Count + " , " + tickNum + " : " + (interpList.Count > 0 ? interpList[0].LastProcessedFrameID.ToString() : ""));

        //enity interpolation
        if (interpolation && interpList.Count >= 2) {

            var state1 = interpList[0];
            var state2 = interpList[1];
            /*Debug.Log("interpolating from tick " + state1.LastProcessedFrameID + " to tick " + state2.LastProcessedFrameID + ", " +
                (curTime - lastTickTime) / (1.0f / tickRate) +
                "lastProcessedTick:" + localPlayer.lastProcessedTickNum);*/
            /*string s = "";
            foreach (var tick in interpList) {
                s += tick.LastProcessedFrameID + " ";
            }
            Debug.Log(s);*/
            var states1 = new Dictionary<int, UpdateShooterTest.PlayerInfo_S_TO_C>();
            var states2 = new Dictionary<int, UpdateShooterTest.PlayerInfo_S_TO_C>();
            foreach (var info in state1.PlayerInfos) {
                states1.Add(info.Id, info);
            }
            foreach (var info in state2.PlayerInfos) {
                states2.Add(info.Id, info);
            }

            foreach (var player in playerMap.Values) {
                if (player.id == localPlayerID) continue;
                UpdateShooterTest.PlayerInfo_S_TO_C playerState1 = null;
                states1.TryGetValue(player.id, out playerState1);
                Vector2 posFrom = playerState1 != null ? new Vector2(playerState1.X, playerState1.Y) : Vector2.zero;
                float rotationFrom = playerState1 != null ? playerState1.Angle : 0;

                UpdateShooterTest.PlayerInfo_S_TO_C playerState2 = null;
                states2.TryGetValue(player.id, out playerState2);
                Vector2 posTo = playerState2 != null ? new Vector2(playerState2.X, playerState2.Y) : Vector2.zero;
                float rotationTo = playerState2 != null ? playerState2.Angle : 0;

                float lerp = (curTime - lastTickTime) / (1.0f / tickRate);
                if (lerp > 1) lerp = 1;
                /*float lerpX = Mathf.Lerp(posFrom.x, posTo.x, lerp);
                float lerpY = Mathf.Lerp(posFrom.y, posTo.y, lerp);*/
                float lerpRot = Mathf.Lerp(rotationFrom, rotationTo, 1);
                Vector2 lerpPos = Vector2.Lerp(posFrom, posTo, lerp);
                Debug.Log($"state1: ({posFrom.x}, {posFrom.y})  state2:({posTo.x}, {posTo.y}) ");
                player.SetTrans(lerpPos.x, lerpPos.y, lerpRot);
                
            }
            Physics2D.Simulate(0.0f);
        }
        if (curTime - lastTickTime >= 1.0f / tickRate) {
            if (!started) return;

            //Debug.Log($"updates.Count:{updates.Count} tick:{tickNum}");

            while (updates.Count > 0) {
                var update = updates.Dequeue();
                HandleUpdatePacket(update);
            }


            if (localPlayer != null) localPlayer.Update_();
            Physics2D.Simulate(1.0f / tickRate);
            tickNum++;

            lastTickTime += 1.0f / tickRate;
        }

        /*foreach (var player in playerMap.Values) {
            
            Debug.Log(player.GetPos().x + " " + player.GetPos().y);

        }*/

        

    }


    public void AddPlayer(int id, float x, float y) {
        GameObject newPlayerObject = Instantiate(playerPrefab, new Vector2(0, 0), Quaternion.identity);
        if (id == localPlayerID) {
            Destroy(newPlayerObject.GetComponent<Player_ShooterTest>());
            localPlayer = newPlayerObject.AddComponent<LocalPlayer_ShooterTest>();
            localPlayer.movement = localPlayer.GetComponent<PlayerMovement_ShooterTest>();
        }
        newPlayerObject.GetComponent<Player_ShooterTest>().Init(id, x, y);
        playerMap.Add(id, newPlayerObject.GetComponent<Player_ShooterTest>());
        Debug.Log("Instantiate player " + id);

        
    }

    public Player_ShooterTest GetPlayerByID(int id) {
        Player_ShooterTest player = null;
        playerMap.TryGetValue(id, out player);
        return player;
    }

    public void CompareAndReconcile(UpdateShooterTest.PlayerInfo_S_TO_C playerInfo, int comfirmTick) {
        var tmp = comfirmTick + 1;

        var inputs = localPlayer.inputsList;
        var states = localPlayer.statesList;

        localPlayer.SetTrans(playerInfo.X, playerInfo.Y, playerInfo.Angle);

        //bool alwaysReconcile = true;
        
        states[(comfirmTick + 1) % 1024].pos = new Vector2(playerInfo.X, playerInfo.Y);
        states[(comfirmTick + 1) % 1024].rotation = playerInfo.Angle;
        comfirmTick++;


        while (comfirmTick <= tickNum - 1) {
            var input = inputs[comfirmTick % 1024];
            localPlayer.ApplyInput(input);
            Physics2D.Simulate(1.0f/tickRate);
            comfirmTick++;
            states[comfirmTick % 1024] = localPlayer.GenerateCurrentPlayerState();

        }
        Debug.Log("reconcile tick " + tmp.ToString() + " to tick " + tickNum.ToString());
    }

    public void HandleUpdatePacket(UpdateShooterTest.UpdateInfo_S_TO_C msg) {
        int frameID = msg.LastProcessedFrameID;
        if (localPlayer != null&&frameID <= localPlayer.lastProcessedTickNum) return;
        //Debug.Log("msg.PlayerInfos.size: " + msg.PlayerInfos.Count);


        //剔除lastProcessedTick之前的状态缓存
        //tick+1为当前正在进行的一个tick
        interpList.Add(msg);
        if (interpList.Count > 0) {
            while (localPlayer != null &&interpList.Count > 0 && interpList[0].LastProcessedFrameID < localPlayer.lastProcessedTickNum - interpRatio - 1) 
                interpList.Remove(interpList[0]);
        }
        


        PlayerStates_ShooterTest state = null ;
        if(localPlayer != null) state = localPlayer.statesList[(frameID + 1) % 1024];
        bool needReconcile = false;
        UpdateShooterTest.PlayerInfo_S_TO_C localPlayerInfo = null;

        foreach (var info in msg.PlayerInfos) {
            //Debug.Log("player_" + info.Id + ", x:" + info.X + ", y:" + info.Y + ", angle:" + info.Angle);
            if (!playerMap.ContainsKey(info.Id)) {
                AddPlayer(info.Id, info.X, info.Y);
            }
            Player_ShooterTest player = GetPlayerByID(info.Id);
            //保存本地玩家的更新信息
            if (info.Id == localPlayerID) {
                float diffPos = 0, diffRot = 0;
                if (state != null) {
                   // Debug.Log($"{frameID}:   state: {state.pos.x}, {state.pos.y} ; info: {info.X}, {info.Y}");
                    diffPos = (state.pos - (new Vector2(info.X, info.Y))).magnitude;
                    diffRot = Mathf.Abs( state.rotation - info.Angle);

                    //Debug.Log($"playerid: {info.Id}, predicted: ({state.pos.x} ,{state.pos.y}) {state.rotation}, acknowledged: ({info.X}, {info.Y}) {info.Angle} ");
                }
                if (state != null && ((diffPos >= maxDiffPos) || (diffRot >= maxDiffRot))) {
                //if (state != null && ((diffPos >= maxDiffPos) )) {
                    //Debug.Log("need reconcile");
                    localPlayerInfo = info;
                    needReconcile = true;
                    
                }
                localPlayer.lastProcessedTickNum = frameID;

                //没有开启回滚修正，则直接修改
                if(!reconciliation) localPlayer.SetTrans(info.X, info.Y, info.Angle);
                localPlayer.SetShodowTrans(new Vector2(info.X, info.Y), info.Angle);

            }
            else {
                if(!interpolation)
                    player.SetTrans(info.X, info.Y, info.Angle);

            }
            player?.ZeroSpeed();
        }

        //Physics2D.Simulate(0.0f);

        //如果是本地玩家，并且开启了回滚修正，则进行
        if (reconciliation && needReconcile) {
            CompareAndReconcile(localPlayerInfo, frameID);
        }
        foreach (var info in msg.PlayerInfos) {
            
            Player_ShooterTest player = GetPlayerByID(info.Id);
            
            player?.ZeroSpeed();
        }
    }

    public void SetPrediction(bool t) {
        prediction = t;
    }

    public void SetReconciliation(bool t) {
        reconciliation = t;
    }

    public void SetInterpolation(bool t) {
        interpolation = t;
    }
}
