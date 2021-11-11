#ifndef SERVER_HANDLE
#define SERVER_HANDLE
#include "game.h"
#include "message.pb.h"
#include "packet.h"
#include <assert.h>

namespace SERVER_HANDLE {

void HandlePlayerInput(int conv, char *buf, int sze) {
    //std::cout << "handling player input..." << std::endl;
    Update_ShooterTest::PlayerInput_C_TO_S newMsg;
    if (!newMsg.ParseFromArray(buf, sze))
        return;
    //std::cout << "parse finished..." << std::endl;
    //std::cout << conv << " " << newMsg.id() << std::endl;
    Player* player = Game::GetInstance().GetSlots()[Game::GetInstance().GetPlayerMap()[newMsg.id()]];
    player->GetPlayerInputQueue()->push(newMsg);
}
}; // namespace SERVER_HANDLE

#endif