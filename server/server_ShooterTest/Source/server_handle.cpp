#include "server_handle.h"
#include "server_send.h"

void SERVER_HANDLE::HandlePlayerInputs(int id, char *buf, int sze) {
    //std::cout << "handling player inputs..." << std::endl;
    Update_ShooterTest::PlayerInputs_C_TO_S newMsg;
    if (!newMsg.ParseFromArray(buf, sze))
        return;
    //std::cout << "parse finished..." << std::endl;
    //std::cout << conv << " " << newMsg.id() << std::endl;



    auto player = Game::GetInstance().GetPlayerBySlotid(id);
    // if(player->GetPlayerInputQueue()->size() < 4)

    player->TryAddToPlayerInputQueue(newMsg);
}


void SERVER_HANDLE::HandlePlayerNickname(int id, char *buf, int sze){
    Update_ShooterTest::PlayerNickname_C_TO_S newMsg;
    if(!newMsg.ParseFromArray(buf, sze)) return;

    auto player = Game::GetInstance().GetPlayerBySlotid(id);

    player->SetNickname(newMsg.nickname());
    printf("player %d's nickname set to %s\n", id, newMsg.nickname().c_str());

    if(!Game::GetInstance().HasStarted()) Game::GetInstance().StartGame();

    //spawn the new player in other player's world
    Packet *packet = new Packet(Update_ShooterTest::TYPE::spawnPlayer_S_TO_C);
    Update_ShooterTest::SpawnPlayer_S_TO_C msg;
    msg.set_slotid(id);
    msg.set_nickname(player->GetNickname());
    msg.set_x(player->GetPos().x);
    msg.set_y(player->GetPos().y);
    msg.set_angle(player->GetRotation());
    char tmp[2048];
    msg.SerializeToArray(tmp, msg.ByteSizeLong());
    packet->AddVal(tmp, msg.ByteSizeLong());
    packet->InsertLengthInFront();

    for(int i = 1; i <= Game::GetInstance().GetMaxPlayerCnt(); i++){
        if(Game::GetInstance().GetPlayerBySlotid(i) == nullptr || Game::GetInstance().GetPlayerBySlotid(i)->IsAI()) continue;
        SERVER_SEND::SpawnPlayer(packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength(), i);
    }
    
    delete packet;
    packet = nullptr;
    //spawn other players in the new player's world
    for(int i = 1; i <= Game::GetInstance().GetMaxPlayerCnt(); i++){
        if(Game::GetInstance().GetPlayerBySlotid(i) == nullptr) continue;
        if(i == id) continue;
        packet = new Packet(Update_ShooterTest::TYPE::spawnPlayer_S_TO_C);
        msg.set_slotid(i);
        player = Game::GetInstance().GetPlayerBySlotid(i);
        msg.set_nickname(player->GetNickname());
        msg.set_x(player->GetPos().x);
        msg.set_y(player->GetPos().y);
        msg.set_angle(player->GetRotation());
        char tmp[2048];
        msg.SerializeToArray(tmp, msg.ByteSizeLong());
        packet->AddVal(tmp, msg.ByteSizeLong());
        packet->InsertLengthInFront();
        
        SERVER_SEND::SpawnPlayer(packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength(), id);

        delete packet;
        packet = nullptr;
    }
}
void SERVER_HANDLE::HandleRttTimeMeasure(int id, char *buf, int sze) {
    Update_ShooterTest::RttMeasure_C_TO_S newMsg;
    if(!newMsg.ParseFromArray(buf, sze)) return;

    int reqId = newMsg.packetid();
    double avgRttTime = newMsg.rtttime();
    auto player = Game::GetInstance().GetPlayerBySlotid(id);
        
    player->SetAvgRttTime(avgRttTime);
    //printf("reqId: %d, avgRttTime: %lf\n", reqId, avgRttTime);
    SERVER_SEND::RttTimeMeasure(id, reqId);
}