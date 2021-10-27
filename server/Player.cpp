#include "Player.h"

Player::Player(unsigned int _id, Game *_game, b2Body *_body_ptr)
    : id(_id), game(_game), body(_body_ptr) {}

Player::~Player() {
    if (playerInfoPtr != nullptr)
        delete playerInfoPtr;
}

float Player::GetPositionWorldX() {
    return body->GetPosition().x;
}

float Player::GetPositionWorldY() {
    return body->GetPosition().y;
}

float Player::GetAngleInRadian() {
    return body->GetAngle();
}

float Player::GetAngleInDegree() {
    return GetAngleInRadian() / M_PI * 180.0f;
}

float Player::GetPositionPixelX() {
    return GetPositionWorldX() * PIXEL_PER_METER;
}

float Player::GetPositionPixelY() {
    return GetPositionWorldY() * PIXEL_PER_METER;
}