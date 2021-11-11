#include "PlayerMovement.h"

void PlayerMovement::SetTrans(float x, float y, float rot){
    b2Vec2 pos;
    pos.Set(x, y);
    body->SetTransform(
        pos,
        rot
    );
}

PlayerMovement::PlayerMovement(b2Body* _body):body(_body){}

PlayerMovement::~PlayerMovement(){}
