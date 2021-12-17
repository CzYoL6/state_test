#pragma
#include "game.h"

#include "server_send.h"
#include<chrono>


Game::Game() {
    inputBuffer = new std::queue<Update_ShooterTest::PlayerInput_C_TO_S>;

    updateInfoPtr = new Update_ShooterTest::UpdateInfo_S_TO_C;

    
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);

  
}

Game::~Game() {
    printf("destructing game...\n");
    // for(int i = 1; i <= maxPlayerCnt; i++){
    //     if(slots[i] != nullptr){
    //         delete slots[i];
    //     }
    // }
    if(slots != nullptr){
        delete []slots;
    }
    printf("1\n");
    if (updateInfoPtr != nullptr)
        delete updateInfoPtr;
    printf("2\n");
    if (world != nullptr)
        delete world;
    printf("3\n");
    if(inputBuffer != nullptr)
        delete  inputBuffer;
    
    printf("game destructed.\n"); 
}

void  Game::Init(int max_player_cnt, int tick_rate){
    SetMaxPlayerCnt(max_player_cnt);

    tickRate = tick_rate;
}


// void Game::AddPlayer(int playerID, float x, float angle) {
//     b2BodyDef bodyDef;
//     bodyDef.type = b2_dynamicBody;
//     bodyDef.position.Set(x, 10.0f);
//     bodyDef.angle = angle;
//     b2Body *body = world->CreateBody(&bodyDef);

//     b2PolygonShape polygon;
//     polygon.SetAsBox(1.0f, 1.0f);

//     b2FixtureDef fixtureDef;
//     fixtureDef.shape = &polygon;
//     fixtureDef.density = 1.0f;
//     fixtureDef.friction = 0.3f;
//     body->CreateFixture(&fixtureDef);
//     Player *player = new Player(playerID, this, body);
//     bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(player);

//     player->SetPlayerInfoPtr(updateInfoPtr->add_playerinfos());

//     playerMap[playerID] = player;
// }

b2World *Game::GetWorld() {
    return world;
}

void Game::SimulatePhysics(float time_step, int vel_iter, int pos_iter) {
    world->Step(time_step, vel_iter, pos_iter);
}

int Game::GetPlayerCount() {
    return player_map_socket_to_slotid.size();
}

void Game::StartGame() {
    
    hasStarted = true;
    InitMap();
    timer.Reset();
    accumulator = 0.0;
    testTimer.Reset();
    // last = iclock64();
    printf("game has startd.\n");
}


void Game::StopGame(){
    hasStarted = false;
    printf("game stopped.\n");
}

bool Game::HasStarted() {
    return hasStarted;
}

void Game::InitMap() {
    b2BodyDef bodyDef;
    b2PolygonShape polygon;

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0, -10);
    bodyDef.angle = 0;
    b2Body *body = world->CreateBody(&bodyDef);
    polygon.SetAsBox(18.0f, 0.5f);
    body->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0, 10);
    bodyDef.angle = 0;
    b2Body *body1 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(18.0f, 0.5f);
    body1->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(-18, 0);
    bodyDef.angle = 0;
    b2Body *body2 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(0.5f, 10.0f);
    body2->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(18, 0);
    bodyDef.angle = 0;
    b2Body *body3 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(0.5f, 10.0f);
    body3->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(-10, 0);
    bodyDef.angle = 0;
    b2Body *body4 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(0.5f, 5.0f);
    body4->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(10, 0);
    bodyDef.angle = 0;
    b2Body *body5 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(0.5f, 5.0f);
    body5->CreateFixture(&polygon, 0.0f);
}

void Game::AddToInputBuffer(Update_ShooterTest::PlayerInput_C_TO_S input){
    inputBuffer->push(input);
    //std::cout << "added into the input buffer.." << std::endl;
}

void Game::Update() {
    //simulate
    double physicsTimeStep = 1.0f / (tickRate* 1.0f);
    //two phases of iterations
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    double past = timer.GetElapsedTime();
    accumulator += past;
    timer.Reset();
    //printf("frame time: %lf\n", past);

    while (accumulator >= physicsTimeStep && HasStarted()) {
        Timer timer_;
        timer_.Reset();

        double realTimeStep = testTimer.GetElapsedTime();
        printf("elapsed time: %lf\n", realTimeStep);
        fflush(NULL);
        testTimer.Reset();

        accumulator -= physicsTimeStep;

        tick++;
        updateInfoPtr->set_inputbuffersize(inputBuffer->size());
        
        for(auto iter : player_map_socket_to_slotid){
            Player *player = slots[iter.second];
            Update_ShooterTest::PlayerInput_C_TO_S input;

            int tmp = 0;
            //至少执行一次
            if((player->has_been_full && !player->GetPlayerInputSize() == 0) || player->GetPlayerInputSize() >= 3 ){
                player->has_been_full = true;
                input = player->PopInputFromQueue();
                player->ApplyInput(input);
                tmp++;
            }
            //if(tmp >= 2) std::cout << "!!!" << tick << " " << player->GetConv() << std::endl;
            std::cout << player->GetSlotid() << " " << player->GetPlayerInputSize() << " " << tmp << std::endl;
        }
        SimulatePhysics(physicsTimeStep, velocityIterations, positionIterations);
        for (auto iter = player_map_socket_to_slotid.begin(); iter != player_map_socket_to_slotid.end(); iter++) {
            Player *player = slots[iter->second];
            int lastProcessedTick = player->GetLastProcessedTick();
            updateInfoPtr->set_lastprocessedframeid(lastProcessedTick);
            Update_ShooterTest::PlayerInfo_S_TO_C *info = player->GetPlayerInfoPtr();
            info->set_id(player->GetSlotid());
            info->set_x(player->GetPos().x);
            info->set_y(player->GetPos().y);
            info->set_angle(player->GetRotation());
             
            int socket = player->GetSocket();
            SERVER_SEND::UpdateInfo(socket,updateInfoPtr);
        }

        double consume_time = timer_.GetElapsedTime();
            //printf("consume time:  %lf\n", consume_time);
        isleep(physicsTimeStep * 1000 - consume_time * 1000);
            
    }
    
}

void Game::ApplyInputToPlayer(int id, Update_ShooterTest::PlayerInput_C_TO_S input){
    Player* player = slots[id];
    if(player != nullptr){
        player->ApplyInput(input);
    }
}


Player* Game::AddPlayer(int socket, int id) {
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(-5.0f + id * 2.0f, 0);

    std::uniform_real_distribution<double> dr_anglePi(-M_PI, M_PI);

    bodyDef.angle = dr_anglePi(RandomEngine::GetInstance().GetDre());
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape polygon;
    polygon.SetAsBox(0.5f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    Player *player = new Player(id, socket, this, body);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(player);

   

    player->SetPlayerInfoPtr(updateInfoPtr->add_playerinfos());

    player_map_socket_to_slotid.insert({socket,id});

    return player;

}

void Game::SetMaxPlayerCnt(int cnt){
    std::cout << "max player cnt set to: " <<cnt<< std::endl;
    maxPlayerCnt = cnt;
    //slot 0 is ignored
    slots = new Player*[cnt + 1];
    for(int i = 0; i <= cnt; i++){
        slots[i] = nullptr;
    }
}

void Game::SetSlotidOfSocket(int slotid, int socket){
    if(slotid == -1){
        player_map_socket_to_slotid.erase(socket);
        return;
    }
    player_map_socket_to_slotid[socket] = slotid;

}

void Game::DelPlayerBySlotidAndSocket(int slotid, int socket){
    Player *player = GetPlayerBySlotid(slotid);
    delete player;

    SetSlot(slotid, nullptr);
    SetSlotidOfSocket(-1, socket);

    //clear the updateinfoptr, and add the rest players' into it
    updateInfoPtr->clear_playerinfos();
    for(auto iter : player_map_socket_to_slotid){
        auto x = updateInfoPtr->add_playerinfos();
        int slotid = iter.second;
        Player *player = GetPlayerBySlotid(slotid);
        // delete player->GetPlayerInfoPtr();
        player->SetPlayerInfoPtr(x);
    }
}