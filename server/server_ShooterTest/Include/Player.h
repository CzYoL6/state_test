#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "message.pb.h"
#include "PlayerMovement.h"
#include "message.pb.h"
#include <box2d/box2d.h>
#include <queue>
#include <memory>

#define PLAYER_STATE_BUFFER_SIZE 2048

class Game;
class Player {

enum AI_DIR{
    kLeft,
    kRight,
    kUp,
    kDown
};

private:
    int slotid{0};

    int socket{-1};

    std::string nickname;

    Game *game{nullptr};

    Update_ShooterTest::PlayerInfo_S_TO_C* playerInfoPtr;

    int lastProcessedTickNum{0};

    int lastReceivedTickNum{0};

    float moveSpeed{5.0f};

    std::unique_ptr<PlayerMovement> movement;

    std::unique_ptr<std::queue<Update_ShooterTest::PlayerInput_C_TO_S>> playerInputQueue;

    double avgRttTime;   // average rtt time

    std::unique_ptr<Update_ShooterTest::PlayerInfo_S_TO_C[]> stateInfo;


    bool hasBeenProcessedOnThisSvrTick;

    bool isAI{false};

    AI_DIR dir{AI_DIR::kLeft};

public:
    void RecordPlayerState(int svr_tick);

    bool HasBeenProcessedOnThisSvrTick(){return hasBeenProcessedOnThisSvrTick;}

    void SetProcessedOnThisSvrTick(bool t){hasBeenProcessedOnThisSvrTick = t;}

    Player(int _id, int _socket, Game *_game);

    ~Player();

    int GetSlotid() { return slotid; }

    int GetSocket() { return socket; }

    double GetAvgRttTime() { return avgRttTime;}

    void SetAvgRttTime(double v) ;

    std::string GetNickname(){ return nickname;}

    void SetNickname(std::string _nickname){ nickname = _nickname; }

    Game *GetGame() { return game; }

    void ZeroSpeed() {movement->ZeroSpeed();}

    b2Vec2 GetPos() {return movement->GetPos();}

    float GetRotation() {return movement->GetRotation();}

    b2Body *GetBody() { return movement->GetRigidBody(); }

    void SetBody(b2Body* _b){movement->SetRigidBody(_b);}

    void SetPlayerInfoPtr(Update_ShooterTest::PlayerInfo_S_TO_C *ptr) { playerInfoPtr = ptr; }

    void SetPlayerInfo(const Update_ShooterTest::PlayerInfo_S_TO_C &info);

    Update_ShooterTest::PlayerInfo_S_TO_C *GetPlayerInfoPtr() { return playerInfoPtr; }

    void ApplyInput(const Update_ShooterTest::PlayerInput_C_TO_S& input);

    int GetLastProcessedTick() {return lastProcessedTickNum;}

    bool has_been_full{false};

    void TryAddToPlayerInputQueue(Update_ShooterTest::PlayerInputs_C_TO_S& inputs);

    int GetPlayerInputSize(){ return playerInputQueue->size();}

    Update_ShooterTest::PlayerInput_C_TO_S PopInputFromQueue();
    
    void RollBackToAgo(double timeago);

    void RollForwardBackToPresent();

    bool IsAI(){return isAI;}

    void setAsAI(bool t){isAI = t;}

    void AIChangeDir(bool change);
};

#endif