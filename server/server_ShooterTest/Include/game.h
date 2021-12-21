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
#include <memory>
#include <mutex>

class Player;

#define PLAYER_INPUT_BUFFER_SIZE 3
#define CLIENT_INTERP_RATIO 2


class Game : public Singleton<Game>{
  private:
    unsigned int gameId{0};
    
    int tick{0};

    std::map<int, int> player_map_socket_to_slotid; //[conv, slot_id]

    std::unique_ptr< std::shared_ptr<Player>[] > slots;
  

    bool hasStarted{false};

    std::shared_ptr< b2World > world;

    std::unique_ptr<Update_ShooterTest::UpdateInfo_S_TO_C> updateInfoPtr;

    std::unique_ptr<std::queue<Update_ShooterTest::PlayerInput_C_TO_S>> inputBuffer;

    int maxPlayerCnt;
    
    Timer timer;

    double accumulator;

    Timer testTimer;
    // IINT64 last;


  public:
    std::mutex inputBufferMutex;
    Game();

    ~Game();

    void Init(int max_player_cnt, int tick_rate);
    
    int GetPlayerCount();

    void StartGame();
    
    void StopGame();

    bool HasStarted();

    std::shared_ptr<b2World> GetWorld();

    void SimulatePhysics(float time_step, int vel_iter, int pos_iter);

    void ApplyInputToPlayer(int conv, Update_ShooterTest::PlayerInput_C_TO_S input);

    void InitMap();

    void Update();

    int GetCurTick() { return tick; }

    void AddToInputBuffer(Update_ShooterTest::PlayerInput_C_TO_S input);

    std::shared_ptr<Player> AddPlayer(int socket, int id);

    int tickRate;
    
    void SetMaxPlayerCnt(int cnt);

    int GetMaxPlayerCnt() { return maxPlayerCnt;}

    std::shared_ptr<Player> GetPlayerBySlotid(int slotid) { return slots[slotid];}

    void ResetSlot(int slotid){ slots[slotid].reset();}

    void SetSlot(int slotid, const std::shared_ptr<Player>& player) {slots[slotid] = player;};
    
    int GetSlotidBySocket(int socket) { return player_map_socket_to_slotid[socket]; }

    void SetSlotidOfSocket(int slotid, int socket);

    void DelPlayerBySlotidAndSocket(int slotid, int socket);
    

};