using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private int m_Id;
    public int Id { get { return m_Id; } }
    public int hor = 0, ver = 0;
    public Vector2 position;
    public float angleInDegree;
    private PlayerView m_ViewController;
    public int speed;

    public float speedTimes = 1;

    public void InitPlayer(int id, float x, float y) {
        m_Id = id;
        position = new Vector2(x, y);
        m_ViewController = GetComponent<PlayerView>();
        m_ViewController.Init(this);
    }

    public void Set(float x, float y, float _angleInDegree) {
        position = new Vector2(x, y);
        angleInDegree = _angleInDegree;
    }

    // Start is called before the first frame update
    void Start()
    {
        //TODO
        
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }


    /*public void HandlePlayerCmd(int frameId, Update.ControlInfo_C_TO_S msg) {
        //if (processedFrameID == frameId) return;
        hor = ver = 0;
        
        if (msg.W) ver += 1;
        if (msg.S) ver -= 1;
        if (msg.A) hor -= 1;
        if (msg.D) hor += 1;
        speedTimes = Mathf.Sqrt(1.0f * hor * hor + 1.0f*ver * ver);

        Debug.LogWarning("handling player cmd ... " + "hor:" + hor + ", ver:" + ver);

       // processedFrameID = frameId;
    }*/


}
