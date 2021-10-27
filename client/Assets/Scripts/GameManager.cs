using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour

{
    public static GameManager Instance { get; private set; }

    public bool started;
    public Dictionary<int, Update.UpdateInfo_S_TO_C> infos;
    public Dictionary<int, Player> playerMap;
    public int currentFrameID, newFrameID;

    public GameObject playerPrefab;
    // Start is called before the first frame update


    private float lastTime;

    private void Awake() {
        if (Instance == null) Instance = this;
        
    }
    void Start()
    {
        started = false;
        infos = new Dictionary<int, Update.UpdateInfo_S_TO_C>();
        playerMap = new Dictionary<int, Player>();

    }

    // Update is called once per frame
    void Update()
    {
        //Debug.LogWarning("playerlist count...: " + playerLists.Count);
    }

    public void StartGame() {
        started = true;
        lastTime = Time.time;
    }

    public void AddPlayer(int id, float x, float y) {
        GameObject newPlayerObject = Instantiate(playerPrefab, new Vector2(0, 0), Quaternion.identity);
        newPlayerObject.GetComponent<Player>().InitPlayer(id, x, y);
        playerMap.Add(id, newPlayerObject.GetComponent<Player>());
        Debug.Log("Instantiate player " + id);
        
    }

    public Player GetPlayerById(int id) {

        /*foreach (var player in playerLists) {
            //Debug.LogWarning("playerid:" + player.Id);
            if (player.Id == id) {
                return player;
            }
        }*/
        Player player = null;
        playerMap.TryGetValue(id, out player);
        return player;
    }


    private void FixedUpdate() {
        
    }



}
