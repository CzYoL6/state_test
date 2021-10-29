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

    public GameObject playerPrefab;

    public bool prediction, reconciliation, compensation;

    public float tickRate;

    public float maxDiffPos , maxDiffRot;

    private float lastTickTime;

    public void StartGame() {
        started = true;
        playerMap = new Dictionary<int, Player_ShooterTest>();
        updates = new Queue<UpdateShooterTest.UpdateInfo_S_TO_C>();
        lastTickTime = 0.0f;
        tickNum = 0;
    }
    private void FixedUpdate() {
        

    }

    private void Update() {
        float curTime = Time.time;
        Debug.Log(1.0f/tickRate);
        while(curTime - lastTickTime >= 1.0f / tickRate) {
            NetManager.Instance.Tick();
            if (!started) return;

            Debug.Log($"updates.Count:{updates.Count} tick:{tickNum}");


            while (updates.Count > 0) {
                var update = updates.Dequeue();
                HandleUpdatePacket(update);
            }
            Physics2D.Simulate(1.0f / tickRate);

            if (localPlayer != null) localPlayer.Update_();
            tickNum++;

            lastTickTime += 1.0f / tickRate;
        }

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
        var tmp = comfirmTick;

        var inputs = localPlayer.inputsList;
        var states = localPlayer.statesList;

        localPlayer.SetTrans(playerInfo.X, playerInfo.Y, playerInfo.Angle);

        //bool alwaysReconcile = true;
        
        states[(comfirmTick + 1) % 1024].pos = new Vector2(playerInfo.X, playerInfo.Y);
        states[(comfirmTick + 1) % 1024].rotation = playerInfo.Angle;
        comfirmTick++;

        while (comfirmTick < tickNum - 1) {
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


        PlayerStates_ShooterTest state = null ;
        if(localPlayer != null) state = localPlayer.statesList[(frameID + 1) % 1024];
        bool needReconcile = false;
        UpdateShooterTest.PlayerInfo_S_TO_C localPlayerInfo = null;

        foreach (var info in msg.PlayerInfos) {
            //Debug.Log("player_" + info.Id + ", x:" + info.X + ", y:" + info.Y + ", angle:" + info.Angle);
            if (!playerMap.ContainsKey(info.Id)) {
                AddPlayer(info.Id, info.X, info.Y);
            }

            //保存本地玩家的更新信息
            if (info.Id == localPlayerID) {
                float diffPos = 0, diffRot = 0;
                if (state != null) {
                    diffPos = (state.pos - (new Vector2(info.X, info.Y))).magnitude;
                    diffRot = Mathf.Abs( state.rotation - info.Angle);

                    Debug.Log($"playerid: {info.Id}, predicted: ({state.pos.x} ,{state.pos.y}) {state.rotation}, acknowledged: ({info.X}, {info.Y}) {info.Angle} ");
                }
                if (state != null && ((diffPos >= maxDiffPos) || (diffRot >= maxDiffRot))) {
                //if (state != null && ((diffPos >= maxDiffPos) )) {
                    Debug.Log("need reconcile");
                    localPlayerInfo = info;
                    needReconcile = true;
                    
                }
                localPlayer.lastProcessedTickNum = frameID;

                //没有开启回滚修正，则直接修改
                if(!reconciliation)localPlayer.SetTrans(info.X, info.Y, info.Angle);
                localPlayer.SetShodowTrans(new Vector2(info.X, info.Y), info.Angle);

            }
            else {
                Player_ShooterTest player = GetPlayerByID(info.Id);
                player.SetTrans(info.X, info.Y, info.Angle);
            }
        }

        //如果是本地玩家，并且开启了回滚修正，则进行
        if (reconciliation && needReconcile) {
            CompareAndReconcile(localPlayerInfo, frameID);
        }
    }

    public void SetPrediction(bool t) {
        prediction = t;
    }

    public void SetReconciliation(bool t) {
        reconciliation = t;
    }
}
