//
// Created by omerb on 20/12/2022.
//

#include "Server.h"

Server::Server(int port, std::ostream &stream) : stream(stream) {
    // setting port:
    this->port = port;
    // initializing sockaddr_in:
    this->initSockaddrIn();
}

void Server::initSockaddrIn() {
    this->sockaddrIn.sin_family = AF_INET; // TCP
    this->sockaddrIn.sin_addr.s_addr = INADDR_ANY;
    this->sockaddrIn.sin_port = htons(port);
}

bool Server::initServer() {
    // creating the socket:
    this->socketId = socket(AF_INET, SOCK_STREAM, 0);
    if(socketId < 0) {
        // printing error to the stream and returning false.
        input::print("failed to create a socket!", stream);
        return false;
    }
    input::print("-------------Success creating socket!", stream);
    // binding the port information:
    if(bind(socketId, (struct sockaddr *) &sockaddrIn, sizeof(sockaddrIn)) < 0) {
        // printing error to the stream and returning false.
        input::print("failed binding the port to the socket!", stream);
        return false;
    }
    input::print("-------------Success binding the port to the socket!", stream);

    return true;
}

void Server::closeServer() {
    if(socketId >= 0) {
        close(socketId);
    }
}

int Server::getSocketId() {
    return this->socketId;
}

sockaddr_in Server::getSockaddrIn() {
    return this->sockaddrIn;
}

std::ostream &Server::getStream() {
    return this->stream;
}

bool Server::listenServer(int n) {
    int t = listen(socketId, n);
    return t >= 0;
}


