#ifndef CLIENT_H
#define CLIENT_H

#include "circle_buffer.hpp"
#include "server.h"
#include <mutex>

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
    void TryHandleMessage();
    void SetUdpAddrInitialized(bool t){ udp_addr_initialized = t;}
    bool HasUdpAddrInitialized(){return udp_addr_initialized;}
    // std::mutex recv_buffer_mutex;
    // std::mutex send_buffer_mutex;

private:
    std::unique_ptr<CircleBuffer<char>> tcp_recv_buffer;
    std::unique_ptr<CircleBuffer<char>> tcp_send_buffer;
    sockaddr_in udp_client_addr;
    bool udp_addr_initialized;
    int id;
};

#endif