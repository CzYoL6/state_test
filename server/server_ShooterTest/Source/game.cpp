#pragma
#include "game.h"

#include "server_send.h"
#include<chrono>
#include<thread>


Game::Game() {
    inputBuffer = std::make_unique< std::queue<Update_ShooterTest::PlayerInput_C_TO_S>>();

    updateInfoPtr = std::make_unique<Update_ShooterTest::UpdateInfo_S_TO_C>();

    
    b2Vec2 gravity(0.0f, 0.0f);
    world = std::make_shared< b2World>(gravity);

  
    InitMap();
}

Game::~Game() {
    printf("destructing game...\n");
    // for(int i = 1; i <= maxPlayerCnt; i++){
    //     if(slots[i] != nullptr){
    //         delete slots[i];
    //     }
    // }
    // if(slots != nullptr){
    //     delete []slots;
    //     slots = nullptr;
    // }
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

std::shared_ptr<b2World> Game::GetWorld() {
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
    polygon.SetAsBox(18.0f, 1.5f);
    body->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0, 10);
    bodyDef.angle = 0;
    b2Body *body1 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(18.0f, 1.5f);
    body1->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(-18, 0);
    bodyDef.angle = 0;
    b2Body *body2 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(1.5f, 10.0f);
    body2->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(18, 0);
    bodyDef.angle = 0;
    b2Body *body3 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(1.5f, 10.0f);
    body3->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(-10, 0);
    bodyDef.angle = 0;
    b2Body *body4 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(1.5f, 5.0f);
    body4->CreateFixture(&polygon, 0.0f);

    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(10, 0);
    bodyDef.angle = 0;
    b2Body *body5 = world->CreateBody(&bodyDef);
    polygon.SetAsBox(1.5f, 5.0f);
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

    auto past = timer.GetElapsedTime();
    // std::cout << past << std::endl;
    accumulator += past;
    timer.Reset();
    // printf("%d\n", accumulatorMs);
    //printf("frame time: %lf\n", past);
    // while (accumulator >= physicsTimeStep && HasStarted()) {
    while (accumulator >= physicsTimeStep) {
        Timer timer_;
        timer_.Reset();
        double realTimeStep = testTimer.GetElapsedTime();
        testTimer.Reset();
        //printf("elapsed time: %lf\n", realTimeStep);
        //fflush(NULL);
        

        accumulator -= physicsTimeStep ;

        //Server::GetInstance().Poll();

        tick++;
        updateInfoPtr->set_inputbuffersize(inputBuffer->size());
        for(auto iter : player_map_socket_to_slotid){
            std::shared_ptr<Player> player = slots[iter.second];
            Update_ShooterTest::PlayerInput_C_TO_S input;

            int tmp = 0;
            //至少执行一次

            std::lock_guard<std::mutex> l(inputBufferMutex);
            if((player->has_been_full && !player->GetPlayerInputSize() == 0) || player->GetPlayerInputSize() >= PLAYER_INPUT_BUFFER_SIZE ){
                player->has_been_full = true;
                do{
                    input = player->PopInputFromQueue();
                    player->ApplyInput(input);
                    tmp++;
                }while(player->GetPlayerInputSize() >= PLAYER_INPUT_BUFFER_SIZE);
            }
            //if packet loss is too high and the input buffer is consumed empty, wait till it is fed up
            else if(player->has_been_full && player->GetPlayerInputSize() == 0)
                player->has_been_full = false;
            printf("player %d has %d input packets left, processed %d\n", player->GetSlotid(), player->GetPlayerInputSize(), tmp);
            //if(tmp >= 2) std::cout << "!!!" << tick << " " << player->GetConv() << std::endl;
        }
        SimulatePhysics(physicsTimeStep, velocityIterations, positionIterations);
        
        for(auto iter : player_map_socket_to_slotid){
            std::shared_ptr<Player> player = slots[iter.second];
            player->ZeroSpeed();
        }
        for (auto iter = player_map_socket_to_slotid.begin(); iter != player_map_socket_to_slotid.end(); iter++) {
            std::shared_ptr<Player> player = slots[iter->second];
            int lastProcessedTick = player->GetLastProcessedTick();
            updateInfoPtr->set_lastprocessedframeid(lastProcessedTick);
            Update_ShooterTest::PlayerInfo_S_TO_C info;
            info.set_id(player->GetSlotid());
            info.set_x(player->GetPos().x);
            info.set_y(player->GetPos().y);
            info.set_angle(player->GetRotation());
            player->SetPlayerInfo(info);
             
            int socket = player->GetSocket();
            SERVER_SEND::UpdateInfo(socket,updateInfoPtr);
        }

        double consume_time = timer_.GetElapsedTime();
            //printf("consume time:  %lf\n", consume_time);
        //isleep((physicsTimeStep * 1000 - consume_time * 1000));
        // printf("tick %d\n", GetCurTick());
        std::this_thread::sleep_for(std::chrono::duration<double>((physicsTimeStep - consume_time - accumulator)));
    }
    
}

void Game::ApplyInputToPlayer(int id, Update_ShooterTest::PlayerInput_C_TO_S input){
    auto player = slots[id];
    if(player != nullptr){
        player->ApplyInput(input);
    }
}


std::shared_ptr<Player> Game::AddPlayer(int socket, int id) {
    
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

    std::shared_ptr<Player> player = std::make_shared<Player>(id, socket, this, body);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(player.get());

    player->SetPlayerInfoPtr(updateInfoPtr->add_playerinfos());

    player_map_socket_to_slotid.insert({socket,id});

    return player;

}

void Game::SetMaxPlayerCnt(int cnt){
    std::cout << "max player cnt set to: " <<cnt<< std::endl;
    maxPlayerCnt = cnt;
    //slot 0 is ignored
    slots = std::make_unique< std::shared_ptr<Player>[] >(cnt + 1);
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
    std::shared_ptr<Player> player = GetPlayerBySlotid(slotid);
    

    ResetSlot(slotid);
    SetSlotidOfSocket(-1, socket);

    //clear the updateinfoptr, and add the rest players' into it
    for(auto iter = updateInfoPtr->mutable_playerinfos()->begin(); iter != updateInfoPtr->mutable_playerinfos()->end(); iter++){
        if(&(*iter) == player->GetPlayerInfoPtr()){
            updateInfoPtr->mutable_playerinfos()->erase(iter);
            break;
        }
    }
    world->DestroyBody(player->GetBody());
    player = nullptr;

    

    //send player left message to every one
    for(auto iter : player_map_socket_to_slotid){
        int to_sock = iter.first;
        SERVER_SEND::PlayerLeft(slotid, to_sock);
    }
    
    
}