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

public class ClientSend : MonoBehaviour
{


    #region Packets

    public static void SendAddNewPlayer(float x, float y) {


        Update.AddNewPlayer_C_TO_S msg = new Update.AddNewPlayer_C_TO_S {
            X = x,
            Y = y
        };

        //SendTCPData(_packet);
        NetManager.Instance.SendMessage((int)Update.TYPE.AddNewPlayerCToS, msg);
    }

    public static void SendAddForceToAll() {


        Update.AddForceToAll_C_TO_S msg = new Update.AddForceToAll_C_TO_S {};

        //SendTCPData(_packet);
        NetManager.Instance.SendMessage((int)Update.TYPE.AddForceToAllCToS, msg);
    }


    public static void SendAddForceToThisOne(int id) {


        Update.AddForceToThisOne_C_TO_S msg = new Update.AddForceToThisOne_C_TO_S {Id = id };

        //SendTCPData(_packet);
        NetManager.Instance.SendMessage((int)Update.TYPE.AddForceToThisOneCToS, msg);
    }

    public static void SendAddTorqueToThisOne(int id) {


        Update.AddForceToThisOne_C_TO_S msg = new Update.AddForceToThisOne_C_TO_S { Id = id };

        //SendTCPData(_packet);
        NetManager.Instance.SendMessage((int)Update.TYPE.AddTorqueToThisOneCToS, msg);
    }

    #endregion

}
