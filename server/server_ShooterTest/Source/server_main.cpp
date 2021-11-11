#include "game.h"
#include "kcpserver.h"
#include "server_handle.h"
#include "time_util.h"
#include <math.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include"logger.hpp"

#include <random>

#define MAX_BUF_SIZE 2048
#define MAX_PLAYER_CNT 10

void on_kcp_revc(int conv, char *data, int len) {
    //data: type + protobuf package
    
    assert(len >= 4);
    int type = *(reinterpret_cast<int *>(data));
    auto protoType = (Update_ShooterTest::TYPE)(type);
    //TODO: parse the package

    switch (protoType) {
    case Update_ShooterTest::TYPE::playerInput_C_TO_S: {

        SERVER_HANDLE::HandlePlayerInput(conv, data + 4, len - 4);
        break;
    }
    }

}

void on_session_kick(int conv) {
    printf("conv:%d kicked\n", conv);
}

void on_error_report(const char *data) {
    printf("kcp error:%s\n", data);
    exit(0);
}

void on_new_session(int conv){
    std::cout << "creating a new kcp session and Player conv: " <<conv<< std::endl;
    Player* player = Game::GetInstance().AddPlayer(conv);
    for(int i = 1; i <= Game::GetInstance().GetMaxPlayerCnt(); i++){
        if(Game::GetInstance().GetSlots()[i] == nullptr){
            Game::GetInstance().GetSlots()[i] = player;
            Game::GetInstance().GetPlayerMap()[conv] = i;
            std::cout << "new player added to slot: " <<i<< std::endl;
            break;
        }
    }
    printf("current player cnt: %d\n", Game::GetInstance().GetPlayerCount());
    if(Game::GetInstance().GetPlayerCount() == 1) 
        Game::GetInstance().StartGame();
}


// struct ip_port{
//     uint32_t ip_addr;
//     uint16_t port;
// }client_slots[MAX_PLAYER_CNT];

// void init_udp_server(int &sock, char *ipaddr, int port){
//     //init udp server
//     sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//     if(sock == -1){
//         printf("udp sock create failed.\n");
//         exit(0);
//     }
//     printf("[LOG] udp socket create completed.\n");
//     struct sockaddr_in serveraddr;
//     bzero(&serveraddr, sizeof(serveraddr));
//     serveraddr.sin_family = AF_INET;
//     serveraddr.sin_port = htons(port);
//     inet_pton(AF_INET, ipaddr, &serveraddr.sin_addr);
//     bind(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
//     printf("[LOG] udp socket bind to %s:%d.\n", ipaddr, port);
//     //nonblock
//     bool enable_nonblock = 1;
//     ioctl(sock, FIONBIO, &enable_nonblock);
//     printf("[LOG] udp socket set to non-blocking mode.\n");
    
//     printf("[LOG] udp server successfully launched.\n");
// }

// void init_tcp_listener_server(int &sock, char *ipaddr, int port){
//     //init udp server
//     sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if(sock == -1){
//         printf("tcp sock create failed.\n");
//         exit(0);
//     }
//     printf("[LOG] tcp socket create completed.\n");
//     struct sockaddr_in serveraddr;
//     bzero(&serveraddr, sizeof(serveraddr));
//     serveraddr.sin_family = AF_INET;
//     serveraddr.sin_port = htons(port);
//     inet_pton(AF_INET, ipaddr, &serveraddr.sin_addr);
//     bind(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
//     printf("[LOG] tcp socket bind to %s:%d.\n", ipaddr, port);
//     //nonblock
//     bool enable_nonblock = 1;
//     ioctl(sock, FIONBIO, &enable_nonblock);
//     printf("[LOG] tcp socket set to non-blocking mode.\n");
    
//     printf("[LOG] tcp udp server successfully launched.\n");
// }

void signal_exit(int signum){
    printf("\nserver terminated. \n");
    exit(0);
}

int main(int argc, char **argv) {

    KCPOptions options;
    options.recv_cb = on_kcp_revc;
    options.kick_cb = on_session_kick;
    options.error_reporter = on_error_report;
    options.new_session_cb = on_new_session;
    options.ip = argv[1];
    options.port = atoi(argv[2]);

    
    KCPServer::GetInstance().SetOption(options);
    if (!KCPServer::GetInstance().Start()) {
        printf("server start error");
        exit(0);
    }

    signal(SIGINT, signal_exit);

    //int udp_sock = -1, tcp_listener_sock = -1;

    // init_udp_server(udp_sock, argv[1], atoi(argv[2]));
    // init_tcp_listener_server(tcp_listener_sock, argv[3], atoi(argv[4]));
    Game::GetInstance().SetMaxPlayerCnt(atoi(argv[3]));

    Game::GetInstance().tickRate = atoi(argv[4]);

    while (true) {
        KCPServer::GetInstance().Update();

        // //receive updates
        // while(true){
        //     char buf[MAX_BUF_SIZE];
        //     memset(buf, 0, sizeof(buf));
        //     struct sockaddr from_addr;
        //     bzero(&from_addr, sizeof(from_addr));
        //     int addr_len = sizeof(from_addr);
        //     int ret = recvfrom(udp_sock, buf, MAX_BUF_SIZE, 0, &from_addr, reinterpret_cast<socklen_t*>(&addr_len));
        //     if(ret == -1){
        //         if(errno != EWOULDBLOCK){
        //             printf("recvfrom failed.\n");
        //             exit(0);
        //         }
        //     }
        //     else{
        //         //handle data
        //         printf("len: %d\n", ret);
        //         int type = *(reinterpret_cast<int *>(buf));
        //         auto protoType = (Update_ShooterTest::TYPE)(type);
        //         printf("type: %d\n", type);
        //         //TODO: parse the package

        //         // switch (protoType) {
        //         //     case Update_ShooterTest::TYPE::playerInput_C_TO_S: {

        //         //         SERVER_HANDLE::HandlePlayerInput(conv, data + 4, len - 4);
        //         //         break;
        //         //     }
        //         // }
        //     }

            
        // }

        if (Game::GetInstance().HasStarted()) {
            Game::GetInstance().Update();
            
        }
    }

    return 0;
}
