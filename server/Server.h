//
// Created by omerb on 20/12/2022.
//
#include "../calculate/input.h"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <unistd.h>
#include <arpa/inet.h>
#include "Server.h"
#ifndef A_OUT_SERVER_H
#define A_OUT_SERVER_H


class Server {
private:

    int port;
    int socketId;
    std::ostream& stream;
    sockaddr_in sockaddrIn;
    void initSockaddrIn();

public:

    Server(int port, std::ostream& stream);
    bool initServer();
    void closeServer();



};


#endif //A_OUT_SERVER_H
