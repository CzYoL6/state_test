#include "Player.h"

Player::Player(unsigned int _id, Game *_game, b2Body *_body_ptr)
    : id(_id), game(_game) {
        movement = new PlayerMovement(_body_ptr);
    }

Player::~Player() {
    if (playerInfoPtr != nullptr)
        delete playerInfoPtr;
    if(movement != nullptr)
        delete movement;
}

void Player::ApplyInput(const Update_ShooterTest::PlayerInput_C_TO_S& input){
    lastProcessedTickNum = input.frameid();
    std::cout << "player " << id << " last " << lastProcessedTickNum << std::endl;
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
    movement->SetVel(moveVec);

    //设置朝向
    movement->SetRotation(input.rotation());
}