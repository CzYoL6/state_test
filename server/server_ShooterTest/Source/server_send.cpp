#include "server_send.h"

void SERVER_SEND::UpdateInfo(int socket, Update_ShooterTest::UpdateInfo_S_TO_C *updateInfo){
        //std::cout << "sending update msg..." << std::endl;
    Packet *packet = new Packet(Update_ShooterTest::TYPE::updateInfo_S_TO_C);
    //std::cout << "packet length1: " << packet->GetAllLength() << std::endl;

    char tmp[64 * 1024];
    updateInfo->SerializeToArray(tmp, updateInfo->ByteSizeLong());
    packet->AddVal(tmp, updateInfo->ByteSizeLong());
    //std::cout << "packet length2: " << updateInfo.ByteSizeLong() << " " << packet->GetAllLength() << std::endl;

    packet->InsertLengthInFront();
    //std::cout << "packet length: " << packet->GetAllLength() << std::endl;

    Server::GetInstance().SengThroughUdp(socket, packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength());

    delete packet;
}


void SERVER_SEND::WelcomeToGame(int socket){
    std::cout << "sending welcome msg..." << std::endl;
    Packet *packet = new Packet(Update_ShooterTest::TYPE::welcome_S_TO_C);
    
    Update_ShooterTest::Welcome_S_TO_C msg;
    msg.set_slotid( Game::GetInstance().GetSlotidBySocket(socket));

    char tmp[2048];
    msg.SerializeToArray(tmp, msg.ByteSizeLong());
    packet->AddVal(tmp, msg.ByteSizeLong());
    packet->InsertLengthInFront();

    //printf("send %d bytes through tcp connection.\n", packet->GetAllLength());

    Server::GetInstance().SendThroughTcp(socket, packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength(), true);


    delete packet;

}

void SERVER_SEND::SpawnPlayer(char *new_player_info, int len, int in_which_id){
    
    std::cout << "sending spawning player msg to player " << in_which_id << std::endl;

    //printf("send %d bytes through tcp connection.\n", len);

    int in_which_socket = Game::GetInstance().GetPlayerBySlotid(in_which_id)->GetSocket();

    Server::GetInstance().SendThroughTcp(in_which_socket, new_player_info, len, true);
}