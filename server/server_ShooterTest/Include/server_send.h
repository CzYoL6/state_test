// #ifndef SERVER_SEND
// #define SERVER_SEND
#pragma once

#include "game.h"
#include "server.h"
#include "message.pb.h"
#include "packet.h"
#include <assert.h>

namespace SERVER_SEND {

void WelcomeToGame(int id);

void UpdateInfo(int socket, std::unique_ptr<Update_ShooterTest::UpdateInfo_S_TO_C>& updateInfo);

void SpawnPlayer(char *new_player_info, int len, int in_which_id);

void PlayerLeft(int who_left, int socket);

void RttTimeMeasure(int id, int reqId);

} // namespace SERVER_SEND

// #endif