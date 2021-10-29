#pragma once
#include "Player.h"
#include "message.pb.h"
#include "random_engine.h"
#include "time_util.h"
#include <queue>
#include <box2d/box2d.h>
#include <map>

class Player;

#define PIXEL_PER_METER 1

class Game {
  private:
    unsigned int gameId{0};
    IUINT32 last_time{0};
    int tick{0};
    std::map<int, Player *> playerMap; //[conv(playerID), Player]
    static Game *instance;
    bool hasStarted{false};
    b2World *world{nullptr};
    Update_ShooterTest::UpdateInfo_S_TO_C *updateInfoPtr{nullptr};
    std::queue<Update_ShooterTest::PlayerInput_C_TO_S> *inputBuffer{nullptr};

  public:
    Game(/* args */);
    ~Game();

    static Game *GetInstance();
    int GetPlayerCount();
    std::map<int, Player *> GetPlayerMap();
    void StartGame();
    bool HasStarted();
    b2World *GetWorld();

    void SimulatePhysics(float time_step, int vel_iter, int pos_iter);

    void ApplyInputToPlayer(int conv, Update_ShooterTest::PlayerInput_C_TO_S input);

    void InitMap();

    void Update();

    int GetCurTick() { return tick; }

    void AddToInputBuffer(Update_ShooterTest::PlayerInput_C_TO_S input);

    void AddPlayer(int conv);
};