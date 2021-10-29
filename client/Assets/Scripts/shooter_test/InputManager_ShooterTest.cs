using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputManager_ShooterTest : Singleton<InputManager_ShooterTest>
{
    private bool w, s, a, d;
    private Vector2 mousePos;
    public PlayerInput_ShooterTest SampleInput() {
        w = Input.GetKey(KeyCode.W);
        s = Input.GetKey(KeyCode.S);
        a = Input.GetKey(KeyCode.A);
        d = Input.GetKey(KeyCode.D);
        mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        //Debug.Log("wasd:" + w.ToString() + a.ToString() + s.ToString() + d.ToString());

        PlayerInput_ShooterTest i = new PlayerInput_ShooterTest(w, s, a, d, mousePos.x, mousePos.y, GameManager_ShooterTest.Instance.tickNum);
        return i;

    }

}
