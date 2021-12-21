// #ifndef SERVER_HANDLE
// #define SERVER_HANDLE
#pragma once
#include "game.h"
#include "message.pb.h"
#include "packet.h"
#include <assert.h>

namespace SERVER_HANDLE {

void HandlePlayerNickname(int id, char *buf, int sze);

void HandlePlayerInputs(int id, char *buf, int sze) ;

void HandleRttTimeMeasure(int id, char *buf, int sze) ;

}; // namespace SERVER_HANDLE

// #endif