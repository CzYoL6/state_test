#ifndef CLIENT_H
#define CLIENT_H

#include "circle_buffer.hpp"
#include "server.h"

class Client{

friend class Server;

public:
    Client(int id);
    ~Client();
    void AddToTcpRecvBuffer(char *buf, int len);
    void AddToTcpSendBuffer(char *buf, int len);
    
    void SetUdpClientAddr(const sockaddr_in& addr);
    sockaddr_in* GetUdpClientAddr(){ return &udp_client_addr;}
    int GetId(){return  id;}
    bool TryHandleMessage();
private:
    CircleBuffer<char> *tcp_recv_buffer;
    CircleBuffer<char> *tcp_send_buffer;
    sockaddr_in udp_client_addr;
    int id;
};

#endif