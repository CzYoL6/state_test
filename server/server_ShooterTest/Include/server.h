#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "circle_buffer.hpp"
#include "packet.h"
#include <sys/epoll.h>
#include <fcntl.h>
#include <map>
#include "message.pb.h"
#include<functional>
#include "client.h"
#include "singleton.h"

class Client;

struct MY_ADDR{
    uint32_t ip;
    uint16_t port;
    MY_ADDR(){}
    MY_ADDR(const sockaddr_in& addr){
        ip = addr.sin_addr.s_addr;
        port = addr.sin_port;
    }
    friend const bool operator < (const MY_ADDR& addr1, const MY_ADDR& addr2) {
        if(addr1.ip != addr2.ip) return addr1.ip < addr2.ip;
        return addr1.port < addr2.port;
    }
};

class Server : public Singleton<Server>{
public:
    Server();
    ~Server();
    void Close();
    //start the server
    void Start(const char* tcp_ip, int tcp_port, const char *udp_ip, int udp_port);
    
    //this will be used in a thread
    void Poll();
    bool ParsePacket(int id, char *buf, int len);

    //add the data into the send buffer
    void SendThroughTcp(int socket, char *buf, int len, bool first_attempt); 
    
    //directly send via udp. find the addr associated with the tcp socket
    void SengThroughUdp(int socket, char *buf, int len);

    bool IsRunning() const {return running;}

private:
    std::map<int, Client*> client_map_socket_to_client;
    std::map<MY_ADDR, Client*> client_map_sockaddrin_to_client;

    int  SetNonBlockingMode(int socket);

    //tcp
    int tcp_listen_socket;
    sockaddr_in tcp_listen_addr;
    void SetUpTcpServer(const char *tcp_ip, int tcp_port);

    //udp
    int udp_server_socket;
    sockaddr_in udp_server_addr;
    void SetUpUdpServer(const char *udp_ip, int udp_port);

    //epoll
    int epollfd;
    epoll_event *events;
    void AddEpollEvent(int fd, uint epollevent);
    void DelEpollEvent(int fd);
    void ModEpollEvent(int fd, uint epollevent);
    void SetUpEpoll();

    bool running;

    typedef void (*MESSAGE_HANDLER)(int, char*, int); //id buf len
    //a dictionary for message handler
    // std::map<Update_ShooterTest::TYPE, std::function<void(char*, int)>> *message_handler;
    std::map<Update_ShooterTest::TYPE, MESSAGE_HANDLER> *message_handler;

    //init all message handler
    void InitMessageHandler();


    //called when new connection is established
    void OnNewConnection(int socket, const sockaddr_in &addr);
    //called when connection closed
    void OnConnectionClose(int socket);

};

#endif