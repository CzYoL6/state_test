using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AddForceToThisOne : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Mouse2)) {
            int id = -1;
            RaycastHit2D hit = Physics2D.Raycast(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);

            if (hit.collider != null) {
                Player player = hit.collider.GetComponent<Player>();
                if (player) id = player.Id;
                //and do what you want
                ClientSend.SendAddForceToThisOne(id);
            }
            
        }
    }
}
