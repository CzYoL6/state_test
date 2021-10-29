using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ClientHandle_ShooterTest : MonoBehaviour
{
    public Player player;

    public static void UpdateInfo(Packet _packet) {
        
        //Debug.Log($"Update info.");
        //Debug.Log("UnreadLenght: " + _packet.UnreadLength());
        UpdateShooterTest.UpdateInfo_S_TO_C msg = UpdateShooterTest.UpdateInfo_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
        GameManager_ShooterTest.Instance.updates.Enqueue(msg);

            //TODO: 根据inputbuffer调整tickrate

    }
}
