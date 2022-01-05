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
        _packet.InsertInt(GameManager_ShooterTest.Instance.localPlayerID);
        Client.instance.udp.SendData(_packet.ToArray());
    }

    #region Packets

    public static void SendLocalPlayerInputs() {
        var msg = new UpdateShooterTest.PlayerInputs_C_TO_S();
        msg.Id = GameManager_ShooterTest.Instance.localPlayerID;
        foreach(var i in GameManager_ShooterTest.Instance.localPlayer.inputsToSend) {
            var newInput = new UpdateShooterTest.PlayerInput_C_TO_S {
                W = i.w_Pressed,
                S = i.s_Pressed,
                A = i.a_Pressed,
                D = i.d_Pressed,
                FrameID = i.tickNum,
                MouseX = i.mousePos.x,
                MouseY = i.mousePos.y,
                MouseDown = i.mouseDown
            };
            msg.Inputs.Add(newInput);
        }
        

        //SendTCPData(_packet);
        using(Packet packet = new Packet((int)UpdateShooterTest.TYPE.PlayerInputsCToS)) {
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

    public static void SendRttTimeMeasure(double rttTime, int reqId) {
       
        var msg = new UpdateShooterTest.RttMeasure_C_TO_S {
            RttTime = rttTime,
            PacketId = reqId
        };

        //SendTCPData(_packet);
        using (Packet packet = new Packet((int)UpdateShooterTest.TYPE.RttMeasureCToS)) {
            packet.Write(msg.ToByteArray());
            SendUDPData(packet);
        }
    }

    #endregion

}
