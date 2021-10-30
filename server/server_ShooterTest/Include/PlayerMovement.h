#pragma once
#include<box2d/box2d.h>

class PlayerMovement{
private:
    b2Body *body{nullptr};

public:
    PlayerMovement(b2Body* body);
    ~PlayerMovement();

    b2Body* GetRigidBody(){return body;}
    void SetVel(b2Vec2 vel){body->SetLinearVelocity(vel);}
    void SetRotation(float rotation);
    b2Vec2 GetPos(){return body->GetPosition();}
    float GetRotation(){return body->GetAngle();}
};