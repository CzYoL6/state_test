#pragma once
#include<box2d/box2d.h>

class PlayerMovement{
private:
    b2Body *body{nullptr};

public:
    PlayerMovement(b2Body* body);
    ~PlayerMovement();

    b2Body* GetRigidBody(){return body;}
    void SetRotation(float rotation) {body->SetTransform(body->GetPosition(), rotation);};
    b2Vec2 GetPos(){return body->GetPosition();}
    float GetRotation(){return body->GetAngle();}
    void SetTrans(float x, float y, float rot);
    void SetVel(b2Vec2 vel) {body->SetLinearVelocity(vel);}

    void ZeroSpeed();
};