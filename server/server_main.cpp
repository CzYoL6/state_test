#include "game.h"
#include "kcpserver.h"
#include "server_handle.h"
#include "time_util.h"
#include <math.h>

#include <random>

void on_kcp_revc(int conv, char *data, int len) {
    //data: type + protobuf package

    assert(len >= 4);
    int type = *(reinterpret_cast<int *>(data));
    auto protoType = (Update::TYPE)(type);
    //TODO: parse the package

    switch (protoType) {
    case Update::TYPE::addNewPlayer_C_TO_S: {

        SERVER_HANDLE::AddNewPlayer(data + 4, len - 4);
        break;
    }
    case Update::TYPE::addForceToAll_C_TO_S: {

        SERVER_HANDLE::AddForceToAll();
        break;
    }
    case Update::TYPE::addForceToThisOne_C_TO_S: {

        SERVER_HANDLE::AddForceToThisOne(data + 4, len - 4);
        break;
    }
    case Update::TYPE::addTorqueToThisOne_C_TO_S: {

        SERVER_HANDLE::AddTorqueToThisOne(data + 4, len - 4);
        break;
    }
    }

    //printf("[RECV] conv=%d type=%d package len(%d)\n", conv, type, len - 4);
}

void on_session_kick(int conv) {
    printf("conv:%d kicked\n", conv);
}

void on_error_report(const char *data) {
    printf("kcp error:%s\n", data);
    exit(0);
}

int main(int argc, char **argv) {

    KCPOptions options;
    options.recv_cb = on_kcp_revc;
    options.kick_cb = on_session_kick;
    options.error_reporter = on_error_report;
    options.ip = argv[1];
    options.port = atoi(argv[2]);
    KCPServer *kcp_server = KCPServer::GetInstance();
    kcp_server->SetOption(options);
    if (!kcp_server->Start()) {
        printf("server start error");
        exit(0);
    }

    IUINT32 last_tick = 0;
    float createInterval = 200.0f;
    int tmpCnt = 0;

    std::uniform_real_distribution<double> dr_posX(-16.0f, 16.0f), dr_anglePi(-M_PI, M_PI);

    while (true) {
        kcp_server->Update();
        if (Game::GetInstance()->HasStarted()) {
            Game::GetInstance()->Update();
            if (tmpCnt <= 30) {

                IUINT32 cur_tick = iclock();
                if (cur_tick - last_tick >= createInterval) {
                    //std::cout << Game::GetInstance()->GetFrameId() << std::endl;
                    float randX = dr_posX((RandomEngine::GetInstance())->GetDre());
                    float randAngle = dr_anglePi((RandomEngine::GetInstance())->GetDre());

                    Game::GetInstance()->AddPlayer(++tmpCnt, randX, randAngle);
                    std::cout << tmpCnt << " " << randX << " " << randAngle << std::endl;
                    last_tick = cur_tick;

                    // auto playerMap = Game::GetInstance()->GetPlayerMap();
                    // for (auto iter = playerMap.begin(); iter != playerMap.end(); iter++) {
                    //     Player *player = iter->second;
                    //     std::cout << "player_" << player->GetId() << " x:" << player->GetPositionPixelX() << " y:" << player->GetPositionPixelY() << " angle:" << player->GetAngleInDegree() << std::endl;
                    // }
                }
            }
        }
    }

    return 0;
}
