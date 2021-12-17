#include "server_handle.h"
#include "server_send.h"

void SERVER_HANDLE::HandlePlayerInput(int id, char *buf, int sze) {
    //std::cout << "handling player input..." << std::endl;
    Update_ShooterTest::PlayerInput_C_TO_S newMsg;
    if (!newMsg.ParseFromArray(buf, sze))
        return;
    //std::cout << "parse finished..." << std::endl;
    //std::cout << conv << " " << newMsg.id() << std::endl;
    Player* player = Game::GetInstance().GetPlayerBySlotid(id);
    // if(player->GetPlayerInputQueue()->size() < 4)
    player->AddToPlayerInputQueue(newMsg);
}


void SERVER_HANDLE::HandlePlayerNickname(int id, char *buf, int sze){
    Update_ShooterTest::PlayerNickname_C_TO_S newMsg;
    if(!newMsg.ParseFromArray(buf, sze)) return;

    Player* player = Game::GetInstance().GetPlayerBySlotid(id);

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
        if(Game::GetInstance().GetPlayerBySlotid(i) == nullptr) continue;
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