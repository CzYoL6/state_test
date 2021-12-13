using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LocalPlayer_ShooterTest : Player_ShooterTest
{
    public PlayerStates_ShooterTest[] statesList;
    public PlayerInput_ShooterTest[] inputsList;

    public int lastProcessedTickNum;

    public GameObject shadow;

    public PlayerStates_ShooterTest previous, current;   //对结果进行插值

    public void Awake() {
        lastProcessedTickNum = 0;
        movement = GetComponent<PlayerMovement_ShooterTest>();
        statesList = new  PlayerStates_ShooterTest[1024];
        inputsList = new PlayerInput_ShooterTest[1024];
        shadow = GameObject.Find("Shadow");
        previous = null;
        current = null;
    }


    private void Start() {
        
    }

    public override void Update_() {
        PlayerInput_ShooterTest input = InputManager_ShooterTest.Instance.SampleInput();

        //Debug.Log("!" + input.w_Pressed.ToString() + input.s_Pressed.ToString() + input.a_Pressed.ToString() + input.d_Pressed.ToString());

        
        //predict
        if (GameManager_ShooterTest.Instance.prediction) {
            previous = current;
            ApplyInput(input);
            current = GenerateCurrentPlayerState();
        }
        PlayerStates_ShooterTest state = GenerateCurrentPlayerState();
        statesList[(GameManager_ShooterTest.Instance.tickNum + 1) % 1024] = state;

        inputsList[GameManager_ShooterTest.Instance.tickNum % 1024] = (input);

        


        //send
        ClientSend_ShooterTest.SendLocalPlayerInput(input, MathHelper.TwoPoints2Degree(input.mousePos, movement.GetPos()));
    }

    public override void ApplyInput(PlayerInput_ShooterTest input) {
        base.ApplyInput(input);
        
    }

    public void SetShodowTrans(Vector2 pos, float rotation) {
        shadow.transform.position = pos;
        shadow.transform.rotation = Quaternion.Euler(0, 0, rotation);
    }

}
