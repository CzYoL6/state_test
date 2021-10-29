#include "PlayerMovement.h"

void PlayerMovement::SetRotation(float rotation){
    body->SetTransform(
        body->GetPosition(),
        rotation
    );
}

PlayerMovement::PlayerMovement(b2Body* _body):body(_body){}

PlayerMovement::~PlayerMovement(){}