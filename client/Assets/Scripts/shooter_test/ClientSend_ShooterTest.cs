using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using UnityEngine;
using UnityEngine.UI;
using System.Xml.Serialization;
using Google.Protobuf;

public class ClientSend_ShooterTest : MonoBehaviour
{

    private static void SendTCPData(Packet _packet) {
        Client.instance.tcp.SendData(_packet.ToArray());
    }

    private static void SendUDPData(Packet _packet) {
        Client.instance.udp.SendData(_packet.ToArray());
    }

    #region Packets

    public static void SendLocalPlayerInput(PlayerInput_ShooterTest input, float derivedRotation) {

        var msg = new UpdateShooterTest.PlayerInput_C_TO_S {
            W = input.w_Pressed,
            S = input.s_Pressed,
            A = input.a_Pressed,
            D = input.d_Pressed,
            FrameID = input.tickNum,
            Rotation = derivedRotation,
            Id = GameManager_ShooterTest.Instance.localPlayerID
        };

        //SendTCPData(_packet);
        using(Packet packet = new Packet((int)UpdateShooterTest.TYPE.PlayerInputCToS)) {
            packet.Write(msg.ToByteArray());
            //Debug.Log("sending player input msg, len:" + packet.Length());
            SendUDPData(packet);
        }
    }

    public static void SendNickname(string nickname) {


        var msg = new UpdateShooterTest.PlayerNickname_C_TO_S {
            Nickname = nickname
        };

        //SendTCPData(_packet);
        using (Packet packet = new Packet((int)UpdateShooterTest.TYPE.PlayerNicknameCToS)) {
            packet.Write(msg.ToByteArray());
            packet.WriteLength();
            SendTCPData(packet);
        }
    }
    

    #endregion

}
