using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InfoKeeper : MonoBehaviour
{
    public static InfoKeeper Instance { get; private set; }
    public string ip;
    public int port;

    private void Awake() {
        if (Instance == null) Instance = this;

    }
    
    void Start()
    {
        DontDestroyOnLoad(gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
