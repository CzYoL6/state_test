using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Test : MonoBehaviour
{
    // Start is called before the first frame update
    public string host;
    public int port;
    void Start()
    {
        Application.targetFrameRate = 60;
        Init();
        DontDestroyOnLoad(this);
        /*Client.instance.ConnectToServer(host, port);*/
        int conv = Time.frameCount % 10000;
        NetManager.Instance.InitConnection((uint)conv, host, port);
        GameManager_ShooterTest.Instance.localPlayerID = conv;
        GameManager_ShooterTest.Instance.StartGame();
    }

    private void Init() {
        host = InfoKeeper.Instance.ip;
        port = InfoKeeper.Instance.port;    
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        
        
    }


}
