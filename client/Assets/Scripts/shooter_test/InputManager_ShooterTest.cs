using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputManager_ShooterTest : Singleton<InputManager_ShooterTest>
{
    private bool w, s, a, d, mouseDown;
    private Vector2 mousePos;
    public PlayerInput_ShooterTest SampleInput() {
        w = Input.GetKey(KeyCode.W);
        s = Input.GetKey(KeyCode.S);
        a = Input.GetKey(KeyCode.A);
        d = Input.GetKey(KeyCode.D);
        mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        mouseDown = Input.GetKey(KeyCode.Mouse0);
        //Debug.Log("wasd:" + w.ToString() + a.ToString() + s.ToString() + d.ToString());

        PlayerInput_ShooterTest i = new PlayerInput_ShooterTest(w, s, a, d, mousePos.x, mousePos.y, mouseDown,GameManager_ShooterTest.Instance.tickNum);
        int timeStampInMs = System.DateTime.Now.Millisecond;
        i.timeStampInMs = timeStampInMs;
        return i;

    }

}
