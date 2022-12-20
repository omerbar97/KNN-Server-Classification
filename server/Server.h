//
// Created by omerb on 20/12/2022.
//
#include "../calculate/input.h"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#ifndef A_OUT_SERVER_H
#define A_OUT_SERVER_H


class Server {
private:
    int socketId;
    std::ostream& stream;

};


#endif //A_OUT_SERVER_H
