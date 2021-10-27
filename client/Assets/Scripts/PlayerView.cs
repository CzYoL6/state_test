using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class PlayerView : MonoBehaviour
{
    private Player m_Player;

    // Start is called before the first frame update
    void Start()
    {
    }

    public void Init(Player player)
    {
        m_Player = player;
    }

    // Update is called once per frame
    void Update()
    {
        if (!GameManager.Instance.started) return;
        Vector2 pos = m_Player.position;
        //Debug.Log(m_Player.speedTimes);
        transform.position = Vector2.Lerp(transform.position, pos, .3f);
        //transform.rotation = Quaternion.Euler(new Vector3(0, 0, m_Player.angleInDegree));
        transform.rotation = Quaternion.Lerp(transform.rotation,Quaternion.Euler(new Vector3(0, 0, m_Player.angleInDegree)), .3f);
    }
}
