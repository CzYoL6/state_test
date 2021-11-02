using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement_ShooterTest : MonoBehaviour
{
    public  Rigidbody2D rb;

    private void Start() {
    }

    public void SetVel(Vector2 vel) {
        rb.velocity = vel;
    }

    public void ZeroAngularVel() {
        rb.angularVelocity = 0;
    }

    public void RotateToPoint(Vector2 point) {
        rb.rotation = MathHelper.TwoPoints2Degree(point, rb.position);
    }

    public Vector2 GetPos() {
        return rb.position;
    }

    public float GetRotation() {
        return rb.rotation;
    }

    public void SetPos(Vector2 pos) {
        rb.position = pos;
    }

    public void SetRotation(float rot) {
        rb.rotation = rot;
    }
}
