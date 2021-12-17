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
        //TODO: 根据inputbuffer调整tickrate

    }

    public static void Welcome(Packet _packet) {
        UpdateShooterTest.Welcome_S_TO_C msg = UpdateShooterTest.Welcome_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        int slotid = msg.Slotid;
        Debug.Log("receive welcome message from server. slot id : " + slotid);

        GameManager_ShooterTest.Instance.localPlayerID = slotid;

        Client.instance.udp.Connect(((IPEndPoint)Client.instance.tcp.socket.Client.LocalEndPoint).Port);
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
}
