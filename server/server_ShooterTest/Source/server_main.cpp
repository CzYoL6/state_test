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
    Server::GetInstance().Stop();
    exit(0);
}

void ServerPoll(){
    while(Server::GetInstance().IsRunning()){
        Server::GetInstance().Poll();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main(int argc, char **argv) {
    //freopen("log.txt", "w", stdout);
    signal(SIGINT, signal_exit);

    Game::GetInstance().Init(atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
    Server::GetInstance().Start(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));


    std::thread t(ServerPoll);

    while (Server::GetInstance().IsRunning()) {
        if (Game::GetInstance().HasStarted()) {
            Game::GetInstance().Update();
        }
    }

    if(t.joinable()) t.join();
    return 0;
}
