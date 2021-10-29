#pragma once
#include "Player.h"
#include "message.pb.h"
#include "random_engine.h"
#include "time_util.h"
#include <box2d/box2d.h>
#include <map>

class Player;

#define PIXEL_PER_METER 1

class Game {
  private:
    unsigned int gameId{0};
    IUINT32 last_ticks{0}, last_send_ticks{0};
    int frameId{0};
    std::map<int, Player *> playerMap; //[conv(playerID), Player]
    static Game *instance;
    bool hasStarted{false};
    b2World *world{nullptr};
    Update::UpdateInfo_S_TO_C *updateInfoPtr{nullptr};

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

    void AddPlayer(int playerID, float x, float angle);

    void AddPlayerWithPos(float x, float y);

    void InitGround();

    void Update();

    int GetFrameId() { return frameId; }

    void AddForceToAll();

    void AddForceToThisOne(int id);

    void AddTorqueToThisOne(int id);
};