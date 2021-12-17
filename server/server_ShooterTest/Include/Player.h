#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "message.pb.h"
#include "PlayerMovement.h"
#include "message.pb.h"
#include <box2d/box2d.h>
#include <queue>

class Game;
class Player {
  private:
    int slotid{0};
    int socket{-1};
    std::string nickname;
    Game *game{nullptr};

    Update_ShooterTest::PlayerInfo_S_TO_C *playerInfoPtr{nullptr};

    int lastProcessedTickNum{0};

    float moveSpeed{5.0f};

    PlayerMovement* movement{nullptr};

    std::queue<Update_ShooterTest::PlayerInput_C_TO_S> *playerInputQueue{nullptr};

  public:
    int GetSlotid() { return slotid; }
    int GetSocket() { return socket; }

    std::string GetNickname(){ return nickname;}
    void SetNickname(std::string _nickname){ nickname = _nickname; }

    Game *GetGame() { return game; }
    Player(int _id, int _socket, Game *_game, b2Body *body_ptr);

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

    bool has_been_full{false};

    void AddToPlayerInputQueue(Update_ShooterTest::PlayerInput_C_TO_S input){ playerInputQueue->push(input);}
    int GetPlayerInputSize(){ return playerInputQueue->size();}
    Update_ShooterTest::PlayerInput_C_TO_S PopInputFromQueue();
};

#endif