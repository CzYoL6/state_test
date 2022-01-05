using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player_ShooterTest : MonoBehaviour
{
    public PlayerMovement_ShooterTest movement;

    public int id;
    public float moveSpeed = 5f;


    public void Awake() {
        movement = GetComponent<PlayerMovement_ShooterTest>();
    }

    public virtual void Init(int _id, Vector2 pos, float rot) {
        id = _id;
        //Debug.Log(movement);
        /*movement.SetPos(new Vector2(x, y));
        movement.SetRotation(0f);*/
        movement.SetPos(pos);
        movement.SetRotation(rot);
        
    }

    public void SetTrans(float x, float y, float rot) {
        movement.SetPos(new Vector2(x, y));
        movement.SetRotation(rot);

    }

    public void ZeroSpeed() {
        movement.SetVel(Vector2.zero);
        movement.ZeroAngularVel();
    }

    ///
    /// 设置刚体速度，每一个物理帧模拟一个FixedDeltaTime
    ///
    public virtual void ApplyInput(PlayerInput_ShooterTest input) {
        //设置速度
        Vector2 moveVec = Vector2.zero;
        if (input.w_Pressed) moveVec += new Vector2(0, 1);
        if (input.s_Pressed) moveVec += new Vector2(0, -1);
        if (input.a_Pressed) moveVec += new Vector2(-1, 0);
        if (input.d_Pressed) moveVec += new Vector2(1, 0);
        moveVec.Normalize();
        moveVec *= moveSpeed;
        movement.SetVel(moveVec);

        /*float deltaTime = 1.0f / (GameManager_ShooterTest.Instance.tickRate);
        Vector2 desPos = new Vector2(movement.GetPos().x + moveVec.x * deltaTime, movement.GetPos().y + moveVec.y * deltaTime);
        movement.SetPos(desPos);*/
        

        //设置朝向

        movement.RotateToPoint(input.mousePos);

        
        //Debug.Log(input.w_Pressed.ToString() + input.s_Pressed.ToString() + input.a_Pressed.ToString() + input.d_Pressed.ToString() + " " + moveVec.x + " " + moveVec.y);

    }

    public PlayerStates_ShooterTest GenerateCurrentPlayerState() {
        PlayerStates_ShooterTest state = 
            new PlayerStates_ShooterTest(
                movement.GetPos().x, 
                movement.GetPos().y, 
                movement.GetRotation(), 
                GameManager_ShooterTest.Instance.tickNum
            );
        return state;
    }


    public virtual void Update_() {

    }

    public Vector2 GetPos() {
        return movement.GetPos();
    }

    public float GetRotation() {
        return movement.GetRotation();
    }
}
