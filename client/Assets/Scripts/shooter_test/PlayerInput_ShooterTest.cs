using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerInput_ShooterTest
{
    public int tickNum;
    public bool w_Pressed;
    public bool s_Pressed;
    public bool a_Pressed;
    public bool d_Pressed;
    public Vector2 mousePos;

    public PlayerInput_ShooterTest(bool w, bool s, bool a, bool d, float x, float y, int tick) {
        Reset(w, s, a, d, x, y, tick);
    }

    public  void Reset(bool w, bool s, bool a, bool d, float x, float y, int tick) {
        w_Pressed = w;
        s_Pressed = s;
        a_Pressed = a;
        d_Pressed = d;
        mousePos = new Vector2(x, y);
        tickNum = tick;
    }
}
