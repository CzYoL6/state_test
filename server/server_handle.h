#pragma once
#include "game.h"
#include "message.pb.h"
#include "packet.h"
#include <assert.h>

namespace SERVER_HANDLE {

void AddNewPlayer(char *buf, int sze) {
    std::cout << "add new player..." << std::endl;
    Update::AddNewPlayer_C_TO_S newMsg;
    if (!newMsg.ParseFromArray(buf, sze))
        return;
    float x = newMsg.x();
    float y = newMsg.y();
    Game::GetInstance()->AddPlayerWithPos(x, y);
}

void AddForceToAll() {
    std::cout << "add force to all..." << std::endl;
    Game::GetInstance()->AddForceToAll();
}

void AddForceToThisOne(char *buf, int sze) {
    std::cout << "add force to this one..." << std::endl;
    Update::AddForceToThisOne_C_TO_S newMsg;
    if (!newMsg.ParseFromArray(buf, sze))
        return;
    int id = newMsg.id();
    Game::GetInstance()->AddForceToThisOne(id);
}
void AddTorqueToThisOne(char *buf, int sze) {
    std::cout << "add torque to this one..." << std::endl;
    Update::AddTorqueToThisOne_C_TO_S newMsg;
    if (!newMsg.ParseFromArray(buf, sze))
        return;
    int id = newMsg.id();
    Game::GetInstance()->AddTorqueToThisOne(id);
}
}; // namespace SERVER_HANDLE
