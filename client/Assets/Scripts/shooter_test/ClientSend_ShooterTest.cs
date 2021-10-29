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
        NetManager.Instance.SendMessage((int)UpdateShooterTest.TYPE.PlayerInputCToS, msg);
    }

    #endregion

}
