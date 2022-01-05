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
#include "physics.h"
#include <mutex>

class Player;

#define PLAYER_INPUT_BUFFER_SIZE 3
#define CLIENT_INTERP_RATIO 2


class Game : public Singleton<Game>{
  private:
    int ai_cnt{0};

    unsigned int gameId{0};
    
    int tick{0};

    std::map<int, int> player_map_socket_to_slotid; //[conv, slot_id]

    std::unique_ptr< std::shared_ptr<Player>[] > slots;
  

    bool hasStarted{false};

    std::shared_ptr< b2World > world;

    std::unique_ptr<Update_ShooterTest::UpdateInfo_S_TO_C> updateInfoPtr;

    std::unique_ptr<std::queue<Update_ShooterTest::PlayerInput_C_TO_S>> inputBuffer;

    std::unique_ptr<MyContactListener> myContactListener;

    std::unique_ptr<MyRayCastCallback> myRayCastCallback;

    int maxPlayerCnt;
    
    Timer timer;

    double accumulator;

    Timer testTimer;
    // IINT64 last;

    std::unique_ptr<std::vector<Update_ShooterTest::HitAcknowledged_S_TO_C>> hitInfos;

    int cur_attacker_slotid;


  public:
    void SetAICnt(int v){ai_cnt = v;}

    std::mutex game_state_mutex;

    Game();

    ~Game();

    void Init(int max_player_cnt, int tick_rate, int ai_cnt_);
    
    int GetPlayerCount();

    void StartGame();
    
    void StopGame();

    bool HasStarted();

    std::shared_ptr<b2World> GetWorld();

    void SimulatePhysics(float time_step, int vel_iter, int pos_iter);

    void InitMap();

    void Update();

    int GetCurTick() { return tick; }

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
    
    void RollBackPlayers(int except_slotid, double timeago);

    void RollForwardBackToPresent(int except_slotid);

    void CheckPlayerShoot(int slotid, b2Vec2 dir);

    void AddIntoHitInfos(const Update_ShooterTest::HitAcknowledged_S_TO_C &hit){ hitInfos->push_back(hit);}

    int GetCurAttackerSlotid() {return cur_attacker_slotid;}

    int AddNewPlayer(int socket);

    std::shared_ptr<Player> AddAI(int id);

    int AddNewAI();    
};