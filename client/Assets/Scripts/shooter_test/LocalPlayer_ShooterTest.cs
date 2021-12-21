using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LocalPlayer_ShooterTest : Player_ShooterTest
{
    public PlayerStates_ShooterTest[] statesList;
    public PlayerInput_ShooterTest[] inputsList;
    public Queue<PlayerInput_ShooterTest> inputsToSend;

    public int lastProcessedTickNum;

    public GameObject shadow;

    public PlayerStates_ShooterTest previous, current;   //对结果进行插值

    public void Awake() {
        lastProcessedTickNum = 0;
        movement = GetComponent<PlayerMovement_ShooterTest>();
        statesList = new  PlayerStates_ShooterTest[1024];
        inputsList = new PlayerInput_ShooterTest[1024];
        inputsToSend = new Queue<PlayerInput_ShooterTest>();
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
            if(current != null) SetTrans(current.pos.x, current.pos.y, current.rotation);
            ApplyInput(input);

            Physics2D.Simulate(1.0f / GameManager_ShooterTest.Instance.tickRate);

            previous = current;
            current = GenerateCurrentPlayerState();
        }
        PlayerStates_ShooterTest state = GenerateCurrentPlayerState();
        statesList[(GameManager_ShooterTest.Instance.tickNum + 1) % 1024] = state;

        inputsList[GameManager_ShooterTest.Instance.tickNum % 1024] = (input);

        //send all unacknowledged inputs to server
        inputsToSend.Enqueue(input);
        while(inputsToSend.Count > 0) {
            PlayerInput_ShooterTest i = inputsToSend.Peek();
            if (i.tickNum <= lastProcessedTickNum) inputsToSend.Dequeue();
            else break;
        }

        /*string s = "";
        foreach (var x in inputsToSend) {
            s += x.tickNum + " ";
        }
        Debug.Log(s);*/

        ClientSend_ShooterTest.SendLocalPlayerInputs();
    }

    public override void ApplyInput(PlayerInput_ShooterTest input) {
        base.ApplyInput(input);
        
    }

    public void SetShodowTrans(Vector2 pos, float rotation) {
        shadow.transform.position = pos;
        shadow.transform.rotation = Quaternion.Euler(0, 0, rotation);
    }

}
