#include "server_send.h"

//will be changed to kcp
void SERVER_SEND::UpdateInfo(Update::UpdateInfo_S_TO_C *updateInfo) {
    //std::cout << "sending update msg..." << std::endl;
    Packet *packet = new Packet(Update::TYPE::updateInfo_S_TO_C);
    //std::cout << "packet length1: " << packet->GetAllLength() << std::endl;

    char tmp[64 * 1024];
    memset(tmp, 0, sizeof(tmp));
    updateInfo->SerializeToArray(tmp, updateInfo->ByteSizeLong());
    packet->AddVal(tmp, updateInfo->ByteSizeLong());
    //std::cout << "packet length2: " << updateInfo.ByteSizeLong() << " " << packet->GetAllLength() << std::endl;

    packet->InsertLengthInFront();
    std::cout << "packet length: " << packet->GetAllLength() << std::endl;

    KCPServer::GetInstance()->SendToAll(packet->GetCircleBuffer()->GetBuffer(), packet->GetAllLength());

    delete packet;
}