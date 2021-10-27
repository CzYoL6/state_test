#pragma
#include "game.h"

#include "server_send.h"

Game *Game::instance = nullptr;

Game::Game() {
}

Game::~Game() {
    if (instance != nullptr)
        delete instance;
    for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++)
        if (iter->second != nullptr)
            delete iter->second;
    if (updateInfoPtr != nullptr)
        delete updateInfoPtr;
    if (world != nullptr)
        delete world;
}

void Game::AddPlayer(int playerID, float x, float angle) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, 10.0f);
    bodyDef.angle = angle;
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape polygon;
    polygon.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    Player *player = new Player(playerID, this, body);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(player);

    player->SetPlayerInfoPtr(updateInfoPtr->add_playerinfos());

    playerMap[playerID] = player;
}

b2World *Game::GetWorld() {
    return world;
}

void Game::SimulatePhysics(float time_step, int vel_iter, int pos_iter) {
    world->Step(time_step, vel_iter, pos_iter);
}

Game *Game::GetInstance() {
    if (instance == nullptr)
        instance = new Game;
    return instance;
}

int Game::GetPlayerCount() {
    return playerMap.size();
}

std::map<int, Player *> Game::GetPlayerMap() {
    return playerMap;
}

void Game::StartGame() {
    updateInfoPtr = new Update::UpdateInfo_S_TO_C;

    hasStarted = true;
    last_ticks = iclock();
    last_send_ticks = last_ticks;

    b2Vec2 gravity(0.0f, -9.81f);
    world = new b2World(gravity);
    InitGround();
}

bool Game::HasStarted() {
    return hasStarted;
}

void Game::InitGround() {
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
}

void Game::Update() {
    float sendTimeStep = 1000.0f / 60.0f;

    //simulate
    float physicsTimeStep = 1000.0f / 128.0f;
    //two phases of iterations
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    IUINT32 cur_tick = iclock();
    if (cur_tick - last_ticks >= physicsTimeStep) {
        float real_time_step = (cur_tick - last_ticks) * 1.0f / 1000.0f;
        //std::cout << "real_time_step: " << real_time_step << std::endl;
        SimulatePhysics(real_time_step, velocityIterations, positionIterations);
        last_ticks = cur_tick;
        frameId++;

        do {
            if (cur_tick - last_send_ticks <= sendTimeStep)
                break;
            last_send_ticks = cur_tick;
            Update::UpdateInfo_S_TO_C *updateInfo = updateInfoPtr;
            updateInfo->set_frameid(frameId);
            for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++) {
                Player *player = iter->second;
                Update::PlayerInfo_S_TO_C *info = player->GetPlayerInfoPtr();
                info->set_x(player->GetPositionPixelX());
                info->set_y(player->GetPositionPixelY());
                info->set_angle(player->GetAngleInDegree());
                info->set_id(player->GetId());
            }

            SERVER_SEND::UpdateInfo(updateInfo);
        } while (true);
    }
}

void Game::AddPlayerWithPos(float x, float y) {
    int playerID = GetPlayerCount() + 1;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    std::uniform_real_distribution<double> dr_anglePi(-M_PI, M_PI);

    bodyDef.angle = dr_anglePi(RandomEngine::GetInstance()->GetDre());
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape polygon;
    polygon.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygon;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    Player *player = new Player(playerID, this, body);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(player);
    playerMap[playerID] = player;

    player->SetPlayerInfoPtr(updateInfoPtr->add_playerinfos());

    std::cout << "add new player_ " << playerID << std::endl;
}

void Game::AddForceToAll() {
    for (auto x = world->GetBodyList(); x; x = x->GetNext()) {
        b2Vec2 up;
        std::uniform_real_distribution<double> dr(-1.0f, 1.0f);
        up.Set(dr(RandomEngine::GetInstance()->GetDre()), dr(RandomEngine::GetInstance()->GetDre()));
        up.Normalize();
        up *= 20.0f;
        x->ApplyLinearImpulseToCenter(up, true);
    }
}

void Game::AddForceToThisOne(int id) {
    Player *player = playerMap[id];
    if (player) {
        b2Vec2 up;
        up.Set(0, 20.0f);
        player->GetBody()->ApplyLinearImpulseToCenter(up, true);
    }
}

void Game::AddTorqueToThisOne(int id) {
    Player *player = playerMap[id];
    if (player) {
        float torque = 1000.0f;
        player->GetBody()->ApplyTorque(torque, true);
    }
}