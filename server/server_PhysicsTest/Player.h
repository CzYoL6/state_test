#pragma once
#include "game.h"
#include "message.pb.h"
#include <box2d/box2d.h>

class Game;
class Player {
  private:
    unsigned int id{0};
    Game *game{nullptr};

    b2Body *body{nullptr};

    Update::PlayerInfo_S_TO_C *playerInfoPtr{nullptr};

  public:
    unsigned int GetId() { return id; }
    Game *GetGame() { return game; }
    Player(unsigned int _id, Game *_game, b2Body *body_ptr);

    ~Player();
    float GetPositionWorldX();
    float GetPositionWorldY();
    float GetAngleInRadian();
    float GetAngleInDegree();

    float GetPositionPixelX();
    float GetPositionPixelY();

    b2Body *GetBody() { return body; }

    void SetPlayerInfoPtr(Update::PlayerInfo_S_TO_C *ptr) { playerInfoPtr = ptr; }
    Update::PlayerInfo_S_TO_C *GetPlayerInfoPtr() { return playerInfoPtr; }
};
