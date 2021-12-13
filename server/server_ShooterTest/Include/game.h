#pragma once
#include "Player.h"
#include "message.pb.h"
#include "random_engine.h"
#include "time_util.h"
#include <queue>
#include <box2d/box2d.h>
#include <map>
#include "singleton.h"
#include<chrono>

class Player;

#define PIXEL_PER_METER 1

class Game : public Singleton<Game>{
  private:
    unsigned int gameId{0};
    
    int tick{0};
    std::map<int, int> playerMap; //[conv, slot_id]
    Player** slots;
    
    bool hasStarted{false};
    b2World *world{nullptr};
    Update_ShooterTest::UpdateInfo_S_TO_C *updateInfoPtr{nullptr};
    std::queue<Update_ShooterTest::PlayerInput_C_TO_S> *inputBuffer{nullptr};

    int maxPlayerCnt;
    Timer timer;
    double accumulator;
    Timer testTimer;
    // IINT64 last;

  public:
    Game(/* args */);
    ~Game();

    int GetPlayerCount();
    std::map<int, int>& GetPlayerMap();
    void StartGame();
    bool HasStarted();
    b2World *GetWorld();

    void SimulatePhysics(float time_step, int vel_iter, int pos_iter);

    void ApplyInputToPlayer(int conv, Update_ShooterTest::PlayerInput_C_TO_S input);

    void InitMap();

    void Update();

    int GetCurTick() { return tick; }

    void AddToInputBuffer(Update_ShooterTest::PlayerInput_C_TO_S input);

    Player* AddPlayer(int conv);

    int tickRate;
    
    void SetMaxPlayerCnt(int cnt){
      std::cout << "max player cnt set to: " <<cnt<< std::endl;
      maxPlayerCnt = cnt;
      slots = new Player*[cnt + 1];
      for(int i = 0; i <= cnt; i++){
        slots[i] = nullptr;
      }
    }
    int GetMaxPlayerCnt(){
      return maxPlayerCnt;
    }
    Player** GetSlots(){
      return slots;
    }
};