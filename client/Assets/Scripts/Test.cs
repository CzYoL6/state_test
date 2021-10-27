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
        Init();
        DontDestroyOnLoad(this);
        /*Client.instance.ConnectToServer(host, port);*/
        NetManager.Instance.InitConnection((uint)Time.frameCount % 1000, host, port);
        GameManager.Instance.StartGame();
    }

    private void Init() {
        host = InfoKeeper.Instance.ip;
        port = InfoKeeper.Instance.port;    
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        
        try {
            NetManager.Instance.Tick();

            if (GameManager.Instance.started) {
                
                
                GlobalEvent.onFixedUpdate.Invoke();

            }
        }
        catch {

        }
    }


}
