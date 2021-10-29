using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MathHelper : MonoBehaviour
{
    public static float TwoPoints2Degree(Vector2 p1, Vector2 p2) {
        Vector3 diff = p2 - p1;
        float rotation = Mathf.Atan2(diff.x, -diff.y) * Mathf.Rad2Deg;
        return rotation;
    }
}
