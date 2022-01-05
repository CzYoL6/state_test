#include "Player.h"
#include "util.h"

Player::Player(int _id, int _socket, Game *_game)
    : slotid(_id), game(_game), socket(_socket), avgRttTime(0) {
        movement = std::make_unique<PlayerMovement>();
        playerInputQueue = std::make_unique<std::queue<Update_ShooterTest::PlayerInput_C_TO_S>>();
        playerInfoPtr = nullptr;
        stateInfo = std::make_unique<Update_ShooterTest::PlayerInfo_S_TO_C[]>(PLAYER_STATE_BUFFER_SIZE);
    }

Player::~Player() {
    printf("destructing player...\n");
    // if (playerInfoPtr != nullptr){
    //     delete playerInfoPtr;
    //     playerInfoPtr = nullptr;
    // }
    // if(movement != nullptr){
    //     delete movement;
    //     movement = nullptr;
    // }
    // if(playerInputQueue != nullptr){
    //     delete playerInputQueue;
    //     playerInputQueue = nullptr;
    // }
    printf("player destructed.\n");
}

void Player::ApplyInput(const Update_ShooterTest::PlayerInput_C_TO_S& input){
    lastProcessedTickNum = input.frameid();
    //std::cout << "player " << id << " last " << lastProcessedTickNum << std::endl;
    //设置速度
    b2Vec2 moveVec = b2Vec2_zero;
    b2Vec2 tmp;
    if (input.w()){
        tmp.Set(0,1);
        moveVec += tmp;
    }
    if (input.s()){
        tmp.Set(0,-1);
        moveVec += tmp;
    }
    if (input.a()){
        tmp.Set(-1,0);
        moveVec += tmp;
    }
    if (input.d()){
        tmp.Set(1,0);
        moveVec += tmp;
    }
    moveVec.Normalize();
    moveVec *= moveSpeed;
    
    movement->SetVel(moveVec);

    // float deltaTime = 1.0f/(Game::GetInstance().tickRate*1.0f);
    // b2Vec2 desPos;
    // desPos.Set(movement->GetPos().x + moveVec.x * deltaTime,
    //         movement->GetPos().y + moveVec.y * deltaTime);
    // movement->SetTrans(desPos.x, desPos.y, 
    //                    TwoPoint2Degree(input.mousex(), input.mousey(), 
    //                                    movement->GetPos().x, movement->GetPos().y
    //                                   )
    //                    );
    movement->SetRotation(TwoPoint2Degree(input.mousex(), input.mousey(), movement->GetPos().x, movement->GetPos().y));
    

    if(input.mousedown()){
        b2Vec2 dir;
        dir.Set(input.mousex(), input.mousey());
        dir -= movement->GetPos();

        Game::GetInstance().CheckPlayerShoot(slotid, dir);
    }
}

void Player::RecordPlayerState(int svr_tick){
    Update_ShooterTest::PlayerInfo_S_TO_C state;
    state.set_x(movement->GetPos().x);
    state.set_y(movement->GetPos().y);
    state.set_angle(movement->GetRotation());

    //no need :)
    state.set_id(GetSlotid());

    stateInfo[svr_tick % PLAYER_STATE_BUFFER_SIZE] = state;
}

Update_ShooterTest::PlayerInput_C_TO_S Player::PopInputFromQueue(){

    Update_ShooterTest::PlayerInput_C_TO_S input = playerInputQueue->front();
    playerInputQueue->pop();
    return input;
}

void Player::SetPlayerInfo(const Update_ShooterTest::PlayerInfo_S_TO_C& info){
    playerInfoPtr->MergeFrom(info);
}

void Player::TryAddToPlayerInputQueue(Update_ShooterTest::PlayerInputs_C_TO_S& inputs){
    for(auto input : inputs.inputs()){
        if(input.frameid() <= lastReceivedTickNum) continue;
        playerInputQueue->push(input);
        lastReceivedTickNum = input.frameid();
    }    


    // printf("player %d's input queue: ", slotid);
    // auto x = *playerInputQueue;
    // while(!x.empty()){
    //     auto y = x.front(); x.pop();
    //     printf("%d ", y.frameid());
    // }
    // printf("\n");
}


void Player::RollBackToAgo(double timeago){
    int tick_num_to_go = Game::GetInstance().GetCurTick() - (timeago / Game::GetInstance().tickRate) - 2;
    const Update_ShooterTest::PlayerInfo_S_TO_C &state = stateInfo[tick_num_to_go % PLAYER_STATE_BUFFER_SIZE];
    movement->SetTrans(state.x(), state.y(), state.angle());
}


void Player::RollForwardBackToPresent(){
    int latest_tick = hasBeenProcessedOnThisSvrTick ? Game::GetInstance().GetCurTick() : (Game::GetInstance().GetCurTick() - 1);
    const Update_ShooterTest::PlayerInfo_S_TO_C &state = stateInfo[latest_tick % PLAYER_STATE_BUFFER_SIZE];
    movement->SetTrans(state.x(), state.y(), state.angle());
}

void Player::SetAvgRttTime(double v){
    avgRttTime = v;
}

void Player::AIChangeDir(bool change){
    if(change){ 
        int _dir = (dir + 1) % 4;
        dir = static_cast<AI_DIR>(_dir);
    }
    if(dir == 0){
        b2Vec2 left;
        left.Set(-2.5f,0);
        movement->SetVel(left);
    }
    else if (dir == 1){
        b2Vec2 right;
        right.Set(2.5f,0);
        movement->SetVel(right);
    }
    else if(dir == 2){
        b2Vec2 up;
        up.Set(0,2.5f);
        movement->SetVel(up);
    }
    else{ 
        b2Vec2 down;
        down.Set(0,-2.5f);
        movement->SetVel(down);
    }
}