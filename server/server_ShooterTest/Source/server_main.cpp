#include "game.h"
#include "kcpserver.h"
#include "server_handle.h"
#include "time_util.h"
#include <math.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include"logger.hpp"
#include "server.h"
#include<thread>


#define MAX_BUF_SIZE 2048
#define MAX_PLAYER_CNT 10


void signal_exit(int signum){
    printf("\nserver terminated. \n");
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, signal_exit);

    Game::GetInstance().Init(atoi(argv[5]), atoi(argv[6]));
    Server::GetInstance().Start(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));

    // std::thread server_thread(&Server::Poll, &server);
    // server_thread.join();

    // while(1);


    while (Server::GetInstance().IsRunning()) {
        Server::GetInstance().Poll();

        if (Game::GetInstance().HasStarted()) {
            Game::GetInstance().Update();
            
        }
    }

    return 0;
}
