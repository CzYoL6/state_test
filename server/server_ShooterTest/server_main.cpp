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
    auto protoType = (Update_ShooterTest::TYPE)(type);
    //TODO: parse the package

    switch (protoType) {
    case Update_ShooterTest::TYPE::playerInput_C_TO_S: {

        SERVER_HANDLE::HandlePlayerInput(conv, data + 4, len - 4);
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

    kcp_server->SetMaxPlayerCnt(atoi(argv[3]));
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
            
        }
    }

    return 0;
}
