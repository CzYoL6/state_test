#include "client.h"


Client::Client(int _id) {
    tcp_recv_buffer = new CircleBuffer<char>(2048);
    tcp_send_buffer = new CircleBuffer<char>(2048);
    memset(&udp_client_addr, 0, sizeof(udp_client_addr));
    id = _id;
}

Client::~Client() {

    printf("destructing client...\n");
    if(tcp_recv_buffer != nullptr) delete tcp_recv_buffer;
    if(tcp_send_buffer != nullptr) delete tcp_send_buffer;
    printf("client destructed.\n");
}


void Client::SetUdpClientAddr(const sockaddr_in& addr){
    memcpy(&udp_client_addr, &addr, sizeof(udp_client_addr));
}

void Client::AddToTcpRecvBuffer(char *buf, int len) {
    tcp_recv_buffer->Write(buf, len);
}

void Client::AddToTcpSendBuffer(char *buf, int len) {
    tcp_send_buffer->Write(buf, len);    
}

bool Client::TryHandleMessage() {
    int msg_len = 0;
    char msg_buf[2048];
    if(tcp_recv_buffer->GetLength() >= sizeof(int)){
        tcp_recv_buffer->Read((char *)&msg_len, sizeof(int), true);
        while(msg_len > 0 && msg_len <= tcp_recv_buffer->GetLength() - sizeof(int)){
            tcp_recv_buffer->Read((char *)&msg_len, sizeof(int));
            tcp_recv_buffer->Read(msg_buf, msg_len);

            Server::GetInstance().ParsePacket(id, msg_buf, msg_len);

            msg_len = 0;
            if(tcp_recv_buffer->GetLength() >= sizeof(int))
                tcp_recv_buffer->Read((char *)&msg_len, sizeof(int), true);
            else break;
        }
    }
}
