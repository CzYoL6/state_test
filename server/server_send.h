#pragma once
#include "game.h"
#include "kcpserver.h"
#include "message.pb.h"
#include "packet.h"
#include <assert.h>

namespace SERVER_SEND {
void UpdateInfo(Update::UpdateInfo_S_TO_C *updateInfo);
} // namespace SERVER_SEND