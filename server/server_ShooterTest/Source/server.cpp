#include "server.h"
#include "server_send.h"
#include "server_handle.h"
#include "Player.h"


Server::Server() {
    message_handler = std::make_unique<std::map<Update_ShooterTest::TYPE, MESSAGE_HANDLER>>();
    tcp_listen_socket = udp_server_socket = -1;
    memset(&tcp_listen_addr, 0, sizeof(tcp_listen_addr));
    memset(&udp_server_addr, 0, sizeof(udp_server_addr));

    client_map_socket_to_client.clear();
    client_map_sockaddrin_to_client.clear();

    events = new epoll_event[50];

    InitMessageHandler();

    running = false;
}

Server::~Server() {
    printf("destructing server...\n");
    Close();
    if(events != nullptr) {
        delete[] events;
        events = nullptr;
    }
    printf("server destructed.\n");
}

void Server::SetUpEpoll(){
   //setting up epoll
    if((epollfd = epoll_create(10)) == -1){
        perror("error creating epoll\n");
        running = false;
    }
    printf("setting up epoll succeeded.\n");
}

void Server::SetUpTcpServer(const char* tcp_ip, int tcp_port){
     //starting tcp listen server
    if((tcp_listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
        perror("error creating tcp listen socket.\n");
        running = false;
    }
    tcp_listen_addr.sin_family = AF_INET;
    tcp_listen_addr.sin_port = htons(tcp_port);
    if(inet_pton(AF_INET, tcp_ip, &tcp_listen_addr.sin_addr) == -1){
        perror("error setting the tcp ip address.\n");
        running = false;
    }
    int one = 1;
    if (setsockopt(tcp_listen_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0) {
        perror("error changing tcp socket option.\n");
        running = false;
    }
    int optval = 1;
    setsockopt(tcp_listen_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(tcp_listen_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    if(bind(tcp_listen_socket, (const struct sockaddr *)&tcp_listen_addr, sizeof(tcp_listen_addr)) == -1){
        perror("error binding tcp socket to address.\n");
        running = false;
    }
    if(listen(tcp_listen_socket, 10) == -1){
        perror("error listening.\n");
        running = false;
    }


    printf("tcp server successfully started at %s:%d, socket %d\n", tcp_ip, tcp_port, tcp_listen_socket);
    AddEpollEvent(tcp_listen_socket, EPOLLIN | EPOLLET);
}

void Server::SetUpUdpServer(const char *udp_ip, int udp_port){
    //starting the udp server
    if((udp_server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("error creating udp  socket.\n");
        running = false;
    }
    udp_server_addr.sin_family = AF_INET;
    udp_server_addr.sin_port = htons(udp_port);
    if(inet_pton(AF_INET, udp_ip, &udp_server_addr.sin_addr) == -1){
        perror("error setting the udp ip address.\n");
        running = false;
    }

    int one = 1;
    if (setsockopt(udp_server_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0) {
        perror("error changing udp socket option.\n");
        running = false;
    }
    int optval = 1;
    setsockopt(udp_server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(udp_server_socket, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    if(bind(udp_server_socket, (const struct sockaddr *)&udp_server_addr, sizeof(udp_server_addr)) == -1){
        perror("error binding udp socket to address.\n");
        running = false;
    }


    printf("udp server successfully started at %s:%d, socket %d\n", udp_ip, udp_port, udp_server_socket);
    AddEpollEvent(udp_server_socket, EPOLLIN | EPOLLET);

    //set the udp server to non-blocking mode
    SetNonBlockingMode(udp_server_socket);
}

void Server::Start(const char* tcp_ip, int tcp_port, const char *udp_ip, int udp_port) {
    running = true;
    SetUpEpoll();
    SetUpTcpServer(tcp_ip, tcp_port);
    SetUpUdpServer(udp_ip, udp_port);
}

bool Server::ParsePacket(int id, char *buf, int len) {
    Update_ShooterTest::TYPE type;
    memcpy(&type, buf, sizeof(Update_ShooterTest::TYPE));
    //printf("handling packet, length: %d, type: %d\n", len,  (int)type);
    MESSAGE_HANDLER msg_h = (*message_handler)[type];

    std::lock_guard<std::mutex> l(Game::GetInstance().game_state_mutex);
    
    msg_h(id, buf + sizeof(Update_ShooterTest::TYPE), len - sizeof(Update_ShooterTest::TYPE));
    //printf("handling finished.\n");
    return true;
}

int  Server::SetNonBlockingMode(int socket){
    int opt;
    if((opt = fcntl(socket, F_GETFL)) == -1){
        perror("error getting the socket option\n");
        running = false;
    }
    if(fcntl(socket, F_SETFL, opt | O_NONBLOCK) == -1){
        perror("error setting the socket option.\n");
        running = false;
    }
    printf("successfully set socket %d to non-blocking mode.\n", socket);
    return opt;
}

void Server::OnNewConnection(int socket, const sockaddr_in &addr){
    std::lock_guard<std::mutex> l(Game::GetInstance().game_state_mutex);
    std::lock_guard<std::mutex> g(server_mutex);
    int slotid = Game::GetInstance().AddNewPlayer(socket);
    
     //create a new client, and player
    std::shared_ptr<Client> new_client = std::make_shared<Client>(slotid);
    client_map_socket_to_client[socket] = new_client;
    // new_client->SetUdpClientAddr(addr);
    // client_map_sockaddrin_to_client.insert({MY_ADDR(addr), new_client});

    printf("adding new player successfully to slot %d, current player count: %d.\n",
        slotid,
        Game::GetInstance().GetPlayerCount());

    SERVER_SEND::WelcomeToGame(socket);

}

void Server::OnConnectionClose(int socket){    
    std::lock_guard<std::mutex> l(Game::GetInstance().game_state_mutex);
    std::lock_guard<std::mutex> g(server_mutex);
    //delete the player
    printf("deleting associated objects.\n");
    auto client = client_map_socket_to_client[socket];
    client_map_sockaddrin_to_client.erase(MY_ADDR(*(client->GetUdpClientAddr())));
    // delete client;
    client_map_socket_to_client.erase(socket);


    int slotid = Game::GetInstance().GetSlotidBySocket(socket);

    Game::GetInstance().DelPlayerBySlotidAndSocket(slotid, socket);

    if(Game::GetInstance().GetPlayerCount()== 0) Game::GetInstance().StopGame();
}

void Server::Poll(){
    // printf("starting epoll\n");


    // while(running){
        int epoll_cnt = epoll_wait(epollfd, events, 50, 0);
        if(epoll_cnt == -1){
            if(errno == EINTR){
                return;
            }
            else{
                perror("error epoll wait.\n");
                running = false;
            }
        }
        for(int i = 0; i < epoll_cnt; i++){
            int fd = events[i].data.fd;
            uint event = events[i].events;
            if(fd == tcp_listen_socket){
                //accept new client
                int new_client_socket = -1;
                sockaddr_in new_tcp_client_addr;
                memset(&new_tcp_client_addr, 0, sizeof(new_tcp_client_addr));
                socklen_t new_cli_addr_len = sizeof(new_tcp_client_addr);
                if((new_client_socket = accept(tcp_listen_socket, (struct sockaddr *)&new_tcp_client_addr, &new_cli_addr_len )) == -1){
                    perror("error accept new connection.\n");
                    running = false;
                }
                //display the ip address str and port number
                char new_cli_ip_addr_str[1024];
                memset(new_cli_ip_addr_str, 0, sizeof(new_cli_ip_addr_str));
                int new_cli_port_number = ntohs(new_tcp_client_addr.sin_port);
                if(inet_ntop(AF_INET, &new_tcp_client_addr.sin_addr, new_cli_ip_addr_str, sizeof(new_cli_ip_addr_str)) ==  nullptr){
                    perror("error getting ip address through inet_ntop.\n");
                    running = false;
                }
                printf("accept new connection (%d--%s:%d)\n", new_client_socket, new_cli_ip_addr_str, new_cli_port_number);

                //set the new connection socket to be non-blocking mode
                SetNonBlockingMode(new_client_socket);

                //add epoll event
                AddEpollEvent(new_client_socket, EPOLLIN | EPOLLET );

                OnNewConnection(new_client_socket, new_tcp_client_addr);
               
            }
            else if(fd == udp_server_socket){
                //receive data from the socket
                //in et mode, we should try our best to receive
                char tmp_buf[2048];
                while(true){
                    memset(tmp_buf, 0, sizeof(tmp_buf));
                    sockaddr_in udp_cli_addr;
                    memset(&udp_cli_addr, 0, sizeof(udp_cli_addr));
                    socklen_t udp_cli_addr_len = sizeof(udp_cli_addr);
                    int ret = recvfrom(fd, tmp_buf, sizeof(tmp_buf), 0, (struct sockaddr *)&udp_cli_addr, &udp_cli_addr_len);
                    if(ret == -1){
                        //fprintf(stderr, "errno: %d\n", errno);
                        if(errno == EINTR) continue;
                        else if(errno == EWOULDBLOCK) break;
                        else{
                            fprintf(stderr, "error receiving data from the udp socket %d.\n", fd);
                            running = false;
                            break;
                        }
                    }
                    else{
                        auto slotid = *((int*)(tmp_buf));

                        //printf("received %d bytes from udp. trying to parse.\n", ret);
                        // auto client = client_map_sockaddrin_to_client[udp_cli_addr];

                        std::shared_ptr<Player> player ;
                        {
                            std::lock_guard<std::mutex> l(Game::GetInstance().game_state_mutex);

                            player = Game::GetInstance().GetPlayerBySlotid(slotid);
                        }
                        if(player == nullptr) {
                            // char new_cli_ip_addr_str[1024];
                            // memset(new_cli_ip_addr_str, 0, sizeof(new_cli_ip_addr_str));
                            // int new_cli_port_number = ntohs(udp_cli_addr.sin_port);
                            // if(inet_ntop(AF_INET, &udp_cli_addr.sin_addr, new_cli_ip_addr_str, sizeof(new_cli_ip_addr_str)) ==  nullptr){
                            //     perror("error getting ip address through inet_ntop.\n");
                            //     running = false;
                            // }
                            // printf("no such client %s:%d.\n", new_cli_ip_addr_str, new_cli_port_number);
                            printf("no such client.\n");
                        }
                            
                        else {
                            // char udp_cli_addr_str[1024];
                            // memset(udp_cli_addr_str, 0, sizeof(udp_cli_addr_str));
                            // int new_cli_port_number = ntohs(udp_cli_addr.sin_port);
                            // if(inet_ntop(AF_INET, &udp_cli_addr.sin_addr, udp_cli_addr_str, sizeof(udp_cli_addr_str)) ==  nullptr){
                            //     perror("error getting ip address through inet_ntop.\n");
                            //     running = false;
                            // }
                            // printf("received udp packet from %s:%d\n", udp_cli_addr_str, new_cli_port_number);
                            auto client = client_map_socket_to_client[player->GetSocket()];
                            if(!client->HasUdpAddrInitialized()){
                                client->SetUdpClientAddr(udp_cli_addr);
                                client_map_sockaddrin_to_client.insert({MY_ADDR(udp_cli_addr), client});
                                client->SetUdpAddrInitialized(true);
                            }
                            ParsePacket(client->GetId(), tmp_buf + 4, ret - 4);

                        }
                    }
                }
            }
            else{
                //tcp client socket
                //in et mode, we should try our best to receive
                if(event & EPOLLIN){
                    char tmp_buf[2048];
                    while(true){
                        memset(tmp_buf, 0, sizeof(tmp_buf));
                        int ret = recv(fd, tmp_buf, sizeof(tmp_buf), 0);
                        if(ret == 0){
                            //connection closed
                            //display the ip address str and port number
                            printf("socket %d closed.\n", fd) ;
                            DelEpollEvent(fd);
                            close(fd);
                            OnConnectionClose(fd);
                            break;
                        }
                        else if(ret == -1){
                            //fprintf(stderr, "errno: %d\n", errno);
                            if(errno == EINTR) continue;
                            else if(errno == EWOULDBLOCK ) break;
                            else{
                                fprintf(stderr, "error receiving data from the tcp client socket %d\n", fd);
                                close(fd);
                                running = false;
                                break;
                            }
                        }
                        else{
                            //printf("received %d bytes from tcp. added to buffer. trying to parse.\n", ret);
                            {
                                client_map_socket_to_client[fd]->AddToTcpRecvBuffer(tmp_buf, ret);
                            }
                            client_map_socket_to_client[fd]->TryHandleMessage();
                        }
                        //adding the data to the circle buffer
                        //remember to add lock and unlock
                    }


                }   

                if(event & EPOLLOUT){
                    char tmp_buf[2048];
                    int sze_to_send;
                    {
                        // std::lock_guard<std::mutex> l(client_map_socket_to_client[fd]->send_buffer_mutex);
                        auto &send_buffer = client_map_socket_to_client[fd]->tcp_send_buffer;
                        sze_to_send = send_buffer->Read(tmp_buf, send_buffer->GetLength());
                    }
                
                    SendThroughTcp(fd, tmp_buf, sze_to_send, false);

                }
                   
            }
        }
    // }
}

void Server::AddEpollEvent(int fd, uint epollevent){
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = epollevent;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1){
        perror("error add epollevent");
        running = false;
    }
}

void Server::DelEpollEvent(int fd){
    epoll_event ev;
    if(epoll_ctl(epollfd,EPOLL_CTL_DEL, fd, &ev) == -1){
        perror("error deleting epoll event");
        running = false;
    }
}
void Server::ModEpollEvent(int fd, uint epollevent){
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = epollevent;
    if(epoll_ctl(epollfd,EPOLL_CTL_MOD, fd, &ev) == -1){
        perror("error modifying epoll event");
        running = false;
    }
}
void  Server::Close(){
    printf("closing the server.\n");
    close(tcp_listen_socket);
    close(udp_server_socket);
    close(epollfd);
}

void Server::InitMessageHandler(){
    message_handler->insert({Update_ShooterTest::TYPE::playerNickname_C_TO_S, &SERVER_HANDLE::HandlePlayerNickname});
    message_handler->insert({Update_ShooterTest::TYPE::playerInputs_C_TO_S, &SERVER_HANDLE::HandlePlayerInputs});
    message_handler->insert({Update_ShooterTest::TYPE::rttMeasure_C_TO_S, &SERVER_HANDLE::HandleRttTimeMeasure});

    printf("message handlers initiated.\n");
}


void Server::SendThroughTcp(int socket, char *buf, int len, bool first_attempt){
resend:
    int ret = send(socket, buf, len, 0);
    if(ret == -1){
        if(errno == EINTR)  goto resend;
        else if(errno == EWOULDBLOCK) {
            client_map_socket_to_client[socket]->AddToTcpSendBuffer(buf, len);
            ModEpollEvent(socket, EPOLLIN | EPOLLOUT | EPOLLET);
        }
        else{
            perror("error sending data.\n");
            running = false;
            return;
        }
    }
    else if(!first_attempt){
        ModEpollEvent(socket, EPOLLIN | EPOLLET);
    }
    else{
        //printf("successfully send on the first attempt.\n");
    }
}   

void Server::SendThroughUdp(int socket, char *buf, int len){
    if(!client_map_socket_to_client[socket]->HasUdpAddrInitialized()) return;

    sockaddr_in* udp_peer_addr = client_map_socket_to_client[socket]->GetUdpClientAddr();
resend_udp:
    // char udp_cli_addr_str[1024];
    // memset(udp_cli_addr_str, 0, sizeof(udp_cli_addr_str));
    // int new_cli_port_number = ntohs(udp_peer_addr->sin_port);
    // if(inet_ntop(AF_INET, &(udp_peer_addr->sin_addr), udp_cli_addr_str, sizeof(udp_cli_addr_str)) ==  nullptr){
    //     perror("error getting ip address through inet_ntop.\n");
    //     running = false;
    // }
    
    // printf("sending udp packet to %s:%d\n", udp_cli_addr_str, new_cli_port_number);
    int ret = sendto(udp_server_socket, buf, len, 0, (const struct sockaddr *)udp_peer_addr, sizeof(*udp_peer_addr));
    if(ret == -1){
        if(errno == EINTR) goto resend_udp;
        else{
            perror("error sending msg through udp.\n");
            running = false;
            return;
        }
    }
    //printf("successfully send out.\n");
}