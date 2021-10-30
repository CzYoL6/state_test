#pragma once
#include "game.h"
#include "message.pb.h"
#include "PlayerMovement.h"
#include <box2d/box2d.h>

class Game;
class Player {
  private:
    int id{0};
    Game *game{nullptr};

    Update_ShooterTest::PlayerInfo_S_TO_C *playerInfoPtr{nullptr};

    int lastProcessedTickNum{0};

    float moveSpeed{5.0f};

    PlayerMovement* movement{nullptr};

  public:
    unsigned int GetId() { return id; }
    Game *GetGame() { return game; }
    Player(unsigned int _id, Game *_game, b2Body *body_ptr);

    ~Player();
    
    b2Vec2 GetPos(){return movement->GetPos();}
    float GetRotation(){return movement->GetRotation();}
    b2Body *GetBody() { return movement->GetRigidBody(); }

    void SetPlayerInfoPtr(Update_ShooterTest::PlayerInfo_S_TO_C *ptr) { playerInfoPtr = ptr; }
    Update_ShooterTest::PlayerInfo_S_TO_C *GetPlayerInfoPtr() { return playerInfoPtr; }

    void ApplyInput(const Update_ShooterTest::PlayerInput_C_TO_S& input);

    int GetLastProcessedTick(){
      
      return lastProcessedTickNum;
    }
};
