using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AddNewPlayer : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Mouse0)) {
            
            Vector2 screenPos = Input.mousePosition;
            Vector2 worldPos = Camera.main.ScreenToWorldPoint(screenPos);
            //Debug.Log("x:" + worldPos.x + ", y:" + worldPos.y);
            ClientSend.SendAddNewPlayer(worldPos.x, worldPos.y);
        }
    }
}
