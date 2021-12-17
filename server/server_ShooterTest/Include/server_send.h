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

void UpdateInfo(int id, Update_ShooterTest::UpdateInfo_S_TO_C *updateInfo);

void SpawnPlayer(char *new_player_info, int len, int in_which_id);

} // namespace SERVER_SEND

// #endif