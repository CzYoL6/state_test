using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ClientHandle_ShooterTest : MonoBehaviour
{
    public Player player;

    public static void UpdateInfo(Packet _packet) {
        GameManager_ShooterTest.Instance.hasRecvFirstPacketFromServer = true;
        //Debug.Log($"Update info.");
        //Debug.Log("UnreadLenght: " + _packet.UnreadLength());
        UpdateShooterTest.UpdateInfo_S_TO_C msg = UpdateShooterTest.UpdateInfo_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        
        GameManager_ShooterTest.Instance.updates.Enqueue(msg);
        //Debug.Log(System.DateTime.Now.Millisecond - GameManager_ShooterTest.Instance.localPlayer.inputsList[msg.LastProcessedFrameID % 1024].timeStampInMs);
        //TODO: 根据inputbuffer调整tickrate

    }

    public static void Welcome(Packet _packet) {
        UpdateShooterTest.Welcome_S_TO_C msg = UpdateShooterTest.Welcome_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        int slotid = msg.Slotid;
        Debug.Log("receive welcome message from server. slot id : " + slotid);

        GameManager_ShooterTest.Instance.localPlayerID = slotid;

        Client.instance.udp.Connect(((IPEndPoint)Client.instance.tcp.socket.Client.LocalEndPoint).Address, ((IPEndPoint)Client.instance.tcp.socket.Client.LocalEndPoint).Port);
        Debug.Log((IPEndPoint)Client.instance.tcp.socket.Client.LocalEndPoint);

       /* ClientSend_ShooterTest.TestUdp();*/


        ClientSend_ShooterTest.SendNickname("pennywise");
    }

    public static void SpawnPlayer(Packet _packet) {
        if (!GameManager_ShooterTest.Instance.started) GameManager_ShooterTest.Instance.StartGame();
        UpdateShooterTest.SpawnPlayer_S_TO_C msg = UpdateShooterTest.SpawnPlayer_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        int slotid = msg.Slotid;
        string nickname = msg.Nickname;
        Vector2 pos = new Vector2(msg.X, msg.Y);
        float rotation = msg.Angle;
        Debug.Log($"receive spawn player message from server. slot id:{slotid}, nickname:{nickname}, pos:({pos.x},{pos.y}), angle:{rotation}");

        GameManager_ShooterTest.Instance.AddPlayer(slotid, pos, rotation);

    }

    public static void PlayerLeft(Packet _packet) {
        UpdateShooterTest.PlayerLeft_S_TO_C msg = UpdateShooterTest.PlayerLeft_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        int slotid = msg.Slotid;
        Debug.Log($"player {slotid} left.");

        GameManager_ShooterTest.Instance.DelPlayer(slotid);

    }

    public static void RttTimeMeasure(Packet _packet) {
        UpdateShooterTest.RttMeasure_S_TO_C msg = UpdateShooterTest.RttMeasure_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        int reqId = msg.PacketId;
        double rtt = Time.realtimeSinceStartupAsDouble - GameManager_ShooterTest.Instance.lastTimeRttPackageSent[reqId % GameManager_ShooterTest.Instance.tickRate];
        GameManager_ShooterTest.Instance.TotalRttTime += rtt;
        GameManager_ShooterTest.Instance.rttTime.Enqueue(rtt);
        while (GameManager_ShooterTest.Instance.rttTime.Count > GameManager_ShooterTest.Instance.tickRate)
            GameManager_ShooterTest.Instance.TotalRttTime -= GameManager_ShooterTest.Instance.rttTime.Dequeue();
        double avgRttTime = (GameManager_ShooterTest.Instance.TotalRttTime / GameManager_ShooterTest.Instance.rttTime.Count);
        Debug.Log("rttTime: " + rtt + " avgTime: " + avgRttTime);


        UIManager.Instance.rttTimeText.SetText(((int)(avgRttTime * 1000)).ToString());

        //ClientSend_ShooterTest.SendRttTimeMeasure(GameManager_ShooterTest.Instance.rttTime, ++GameManager_ShooterTest.Instance.rttTimeReqCnt);

    }

    public static void HitInfo(Packet _packet) {
        UpdateShooterTest.HitAcknowledged_S_TO_C msg = UpdateShooterTest.HitAcknowledged_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        int attackerId = msg.AttackerSlotid;
        int damage = msg.Damage;
        int enemyId = msg.EnemySlotid;
        Vector2 enemyPos = new Vector2(msg.EPosX, msg.EPosY);
        float enemyRot = msg.ERot;
        bool dead = msg.Dead;
        Vector2 attackerPos = new Vector2(msg.APosX, msg.APosY);
        float attackerRot = msg.ARot;
        GameManager_ShooterTest.Instance.hitInfoDebugger.transform.position = enemyPos;
        GameManager_ShooterTest.Instance.hitInfoDebugger.transform.rotation = Quaternion.Euler(0,0,enemyRot);
        GameManager_ShooterTest.Instance.attackerInfoDebugger.transform.position = attackerPos;
        GameManager_ShooterTest.Instance.attackerInfoDebugger.transform.rotation = Quaternion.Euler(0, 0, attackerRot);
        GameManager_ShooterTest.Instance.attackerInfoDebugger.GetComponent<LineRenderer>().SetPosition(0, attackerPos);
        GameManager_ShooterTest.Instance.attackerInfoDebugger.GetComponent<LineRenderer>().SetPosition(1, attackerPos + 
                new Vector2(GameManager_ShooterTest.Instance.attackerInfoDebugger.transform.up.x, GameManager_ShooterTest.Instance.attackerInfoDebugger.transform.up.y) * 5);
    }
}
