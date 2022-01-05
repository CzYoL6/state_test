#include "client.h"


Client::Client(int _id) {
    tcp_recv_buffer = std::make_unique<CircleBuffer<char>>(2048);
    tcp_send_buffer = std::make_unique<CircleBuffer<char>>(2048);
    memset(&udp_client_addr, 0, sizeof(udp_client_addr));
    udp_addr_initialized = false;
    id = _id;
}

Client::~Client() {

    printf("destructing client...\n");
    // if(tcp_recv_buffer != nullptr){
    //     delete tcp_recv_buffer;
    //     tcp_recv_buffer = nullptr;
    // } 
    // if(tcp_send_buffer != nullptr) {
    //     delete tcp_send_buffer;
    //     tcp_send_buffer = nullptr;
    // }
    printf("client destructed.\n");
}


void Client::SetUdpClientAddr(const sockaddr_in& addr){
    memcpy(&udp_client_addr, &addr, sizeof(udp_client_addr));
}

void Client::AddToTcpRecvBuffer(char *buf, int len) {
    // std::lock_guard<std::mutex> l(recv_buffer_mutex);
    tcp_recv_buffer->Write(buf, len);
}

void Client::AddToTcpSendBuffer(char *buf, int len) {
    // std::lock_guard<std::mutex> l(send_buffer_mutex);
    tcp_send_buffer->Write(buf, len);    
}

void Client::TryHandleMessage() {
    int msg_len = 0;
    char msg_buf[2048];

    
    // std::lock_guard<std::mutex> l(recv_buffer_mutex);

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
