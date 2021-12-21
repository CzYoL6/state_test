#include "server_send.h"


void SERVER_SEND::UpdateInfo(int socket, std::unique_ptr<Update_ShooterTest::UpdateInfo_S_TO_C>& updateInfo){

        //std::cout << "sending update msg..." << std::endl;
    std::unique_ptr<Packet> packet = std::make_unique<Packet>(Update_ShooterTest::TYPE::updateInfo_S_TO_C);
    //std::cout << "packet length1: " << packet->GetAllLength() << std::endl;

    char tmp[64 * 1024];
    updateInfo->SerializeToArray(tmp, updateInfo->ByteSizeLong());
    packet->AddVal(tmp, updateInfo->ByteSizeLong());
    //std::cout << "packet length2: " << updateInfo.ByteSizeLong() << " " << packet->GetAllLength() << std::endl;

    //packet->InsertLengthInFront();
    //std::cout << "packet length: " << packet->GetAllLength() << std::endl;

    Server::GetInstance().SengThroughUdp(socket, packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength());
}


void SERVER_SEND::WelcomeToGame(int socket){
    std::cout << "sending welcome msg..." << std::endl;
    std::unique_ptr<Packet> packet = std::make_unique<Packet>(Update_ShooterTest::TYPE::welcome_S_TO_C);
    
    Update_ShooterTest::Welcome_S_TO_C msg;
    msg.set_slotid( Game::GetInstance().GetSlotidBySocket(socket));

    char tmp[2048];
    msg.SerializeToArray(tmp, msg.ByteSizeLong());
    packet->AddVal(tmp, msg.ByteSizeLong());
    packet->InsertLengthInFront();

    //printf("send %d bytes through tcp connection.\n", packet->GetAllLength());

    Server::GetInstance().SendThroughTcp(socket, packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength(), true);


}

void SERVER_SEND::SpawnPlayer(char *new_player_info, int len, int in_which_id){
    
    std::cout << "sending spawning player msg to player " << in_which_id << std::endl;

    //printf("send %d bytes through tcp connection.\n", len);

    int in_which_socket = Game::GetInstance().GetPlayerBySlotid(in_which_id)->GetSocket();

    Server::GetInstance().SendThroughTcp(in_which_socket, new_player_info, len, true);
}



void SERVER_SEND::PlayerLeft(int who_left, int socket){
    
        //std::cout << "sending update msg..." << std::endl;
    std::unique_ptr<Packet> packet = std::make_unique<Packet>(Update_ShooterTest::TYPE::playerLeft_S_TO_C);
    //std::cout << "packet length1: " << packet->GetAllLength() << std::endl;

    Update_ShooterTest::PlayerLeft_S_TO_C msg;
    char tmp[64 * 1024];
    msg.set_slotid(who_left);
    msg.SerializeToArray(tmp, msg.ByteSizeLong());
    packet->AddVal(tmp, msg.ByteSizeLong());
    //std::cout << "packet length2: " << updateInfo.ByteSizeLong() << " " << packet->GetAllLength() << std::endl;

    packet->InsertLengthInFront();
    //std::cout << "packet length: " << packet->GetAllLength() << std::endl;

    Server::GetInstance().SendThroughTcp(socket, packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength(), true);
}




void SERVER_SEND::RttTimeMeasure(int id, int reqId){
    Packet *packet = new Packet(Update_ShooterTest::TYPE::rttMeasure_S_TO_C);
    Update_ShooterTest::RttMeasure_S_TO_C msg;
    msg.set_packetid(reqId);
    char tmp[2048];
    msg.SerializePartialToArray(tmp, msg.ByteSizeLong());
    packet->AddVal(tmp, msg.ByteSizeLong());

    int socket = Game::GetInstance().GetPlayerBySlotid(id)->GetSocket();
    Server::GetInstance().SengThroughUdp(socket, packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength());
    //printf("send!!!%d\n", packet->GetAllLength());
    delete packet;
    packet = nullptr;
}