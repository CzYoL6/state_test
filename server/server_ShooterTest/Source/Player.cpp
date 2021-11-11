#include "Player.h"

Player::Player(unsigned int _id, Game *_game, b2Body *_body_ptr)
    : conv(_id), game(_game) {
        movement = new PlayerMovement(_body_ptr);
        playerInputQueue = new std::queue<Update_ShooterTest::PlayerInput_C_TO_S>;
    }

Player::~Player() {
    if (playerInfoPtr != nullptr)
        delete playerInfoPtr;
    if(movement != nullptr)
        delete movement;
    if(playerInputQueue != nullptr)
        delete playerInputQueue;
}

void Player::ApplyInput(const Update_ShooterTest::PlayerInput_C_TO_S& input){
    lastProcessedTickNum = input.frameid();
    //std::cout << "player " << id << " last " << lastProcessedTickNum << std::endl;
    //设置速度
    b2Vec2 moveVec = b2Vec2_zero;
    b2Vec2 tmp;
    if (input.w()){
        tmp.Set(0,1);
        moveVec += tmp;
    }
    if (input.s()){
        tmp.Set(0,-1);
        moveVec += tmp;
    }
    if (input.a()){
        tmp.Set(-1,0);
        moveVec += tmp;
    }
    if (input.d()){
        tmp.Set(1,0);
        moveVec += tmp;
    }
    moveVec.Normalize();
    moveVec *= moveSpeed;
    //修改：直接使用deltatime修改坐标
    //movement->SetVel(moveVec);

    float deltaTime = 1.0f/(Game::GetInstance().tickRate*1.0f);
    b2Vec2 desPos;
    desPos.Set(movement->GetPos().x + moveVec.x * deltaTime,
            movement->GetPos().y + moveVec.y * deltaTime);
    movement->SetTrans(desPos.x, desPos.y, input.rotation());
}