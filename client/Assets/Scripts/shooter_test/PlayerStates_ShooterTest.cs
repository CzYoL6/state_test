using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStates_ShooterTest
{
    public int tickNum;
    public Vector2 pos;
    public float rotation;

    public PlayerStates_ShooterTest(float x, float y, float r, int tick) {
        Reset(x, y, r, tick);
    }


    public void Reset(float x, float y, float r, int tick) {
        pos = new Vector2(x, y);
        rotation = r;
        tickNum = tick;
    }

}
