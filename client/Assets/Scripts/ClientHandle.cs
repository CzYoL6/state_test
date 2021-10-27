using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ClientHandle : MonoBehaviour
{
    public Player player;

    public static void UpdateInfo(Packet _packet) {
        
        Debug.Log($"Update info.");
        try {
            Debug.Log("UnreadLenght: " + _packet.UnreadLength());
            Update.UpdateInfo_S_TO_C msg = Update.UpdateInfo_S_TO_C.Parser.ParseFrom(_packet.ReadBytes(_packet.UnreadLength()));
            int frameID = msg.FrameID;
            Debug.Log("recv frameID: " + frameID);
            Debug.Log("msg.PlayerInfos.size: " + msg.PlayerInfos.Count);
            foreach (var info in msg.PlayerInfos) {
                Debug.Log("player_" + info.Id + ", x:" + info.X + ", y:" + info.Y + ", angle:" + info.Angle);
                if (!GameManager.Instance.playerMap.ContainsKey(info.Id)) {
                    GameManager.Instance.AddPlayer(info.Id, info.X, info.Y);
                }
                Player player = GameManager.Instance.GetPlayerById(info.Id);
                player.Set(info.X, info.Y, info.Angle);
            }
        }
        catch(Exception e) {
            Debug.LogError(e);
        }
        
        //GameManager.Instance.infos.Add(frameID, msg);
        //GameManager.Instance.newFrameID = frameID;

        //Client.instance.myId = _myId;
        //send welcome received packet

        //ClientSend.WelcomeReceived();
    }
}
