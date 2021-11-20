#pragma
#include "game.h"

#include "server_send.h"
#include<chrono>


Game::Game() {
    inputBuffer = new std::queue<Update_ShooterTest::PlayerInput_C_TO_S>;

    updateInfoPtr = new Update_ShooterTest::UpdateInfo_S_TO_C;

    
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);
    InitMap();

}

Game::~Game() {
    // for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++)
    //     if (iter->second != -1)
    //         delete slots[iter->second];
    if(slots != nullptr){
        delete []slots;
    }
    if (updateInfoPtr != nullptr)
        delete updateInfoPtr;
    if (world != nullptr)
        delete world;
    if(inputBuffer != nullptr)
        delete  inputBuffer;
    
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
    return playerMap.size();
}

std::map<int, int>& Game::GetPlayerMap() {
    return playerMap;
}

void Game::StartGame() {
    
    hasStarted = true;
    last_time = std::chrono::system_clock::now();

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
    float physicsTimeStep = 1.0f / (tickRate* 1.0f);
    //two phases of iterations
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    std::chrono::system_clock::time_point cur_tick = std::chrono::system_clock::now();
    std::chrono::duration<float> time_step = cur_tick - last_time;

    //std::cout << time_step.count()<< std::endl;
    if (time_step.count() >= physicsTimeStep && HasStarted()) {
        //KCPServer::GetInstance().Update();

        
        last_time = cur_tick;

        //last_time = cur_tick;
        tick++;
        //std::cout<<"tick:" <<tick<<std::endl;
        //update the input buffer size
        updateInfoPtr->set_inputbuffersize(inputBuffer->size());
        //std::cout << inputBuffer->size() << std::endl;
        // while(!inputBuffer->empty()){
        //     auto input = inputBuffer->front();
        //     inputBuffer->pop();

        //     int playerID = input.id();
        //     Player*player = playerMap[playerID];
        //     if(player != nullptr){
        //         if(input.frameid() <= player->GetLastProcessedTick()) continue;
        //         else{
        //             player->ApplyInput(input);
        //         }
        //     }
        // }
        for(auto iter : playerMap){
            Player *player = slots[iter.second];
            Update_ShooterTest::PlayerInput_C_TO_S input;


            int tmp = 0;
            //至少执行一次
            if((player->has_been_full && !player->GetPlayerInputQueue()->empty()) || player->GetPlayerInputQueue()->size() >= 3 ){
                player->has_been_full = true;
                input = player->GetPlayerInputQueue()->front();
                player->GetPlayerInputQueue()->pop();
                player->ApplyInput(input);
                tmp++;
            }
            //if(tmp >= 2) std::cout << "!!!" << tick << " " << player->GetConv() << std::endl;
            std::cout << player->GetConv() << " " << player->GetPlayerInputQueue()->size() << " " << tmp << std::endl;
        }
        SimulatePhysics(1.0f/(tickRate* 1.0f), velocityIterations, positionIterations);
        for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++) {
            Player *player = slots[iter->second];
            int lastProcessedTick = player->GetLastProcessedTick();
            updateInfoPtr->set_lastprocessedframeid(lastProcessedTick);
            Update_ShooterTest::PlayerInfo_S_TO_C *info = player->GetPlayerInfoPtr();
            info->set_id(player->GetConv());
            info->set_x(player->GetPos().x);
            info->set_y(player->GetPos().y);
            info->set_angle(player->GetRotation());
            
            SERVER_SEND::UpdateInfo(player->GetConv(),updateInfoPtr);
        }

        
        
    }
    
}

void Game::ApplyInputToPlayer(int conv, Update_ShooterTest::PlayerInput_C_TO_S input){
    Player* player = slots[playerMap[conv]];
    if(player != nullptr){
        player->ApplyInput(input);
    }
}


Player* Game::AddPlayer(int conv) {
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 0);

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

    Player *player = new Player(conv, this, body);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(player);

   

    player->SetPlayerInfoPtr(updateInfoPtr->add_playerinfos());

    std::cout << "adding player " << conv<< " cnt:"<<playerMap.size() << std::endl;
    return player;

}