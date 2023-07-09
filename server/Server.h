//
// Created by omerb on 20/12/2022.
//
#include "../src/input.h"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <unistd.h>
#include <arpa/inet.h>
#ifndef A_OUT_SERVER_H
#define A_OUT_SERVER_H

class Server {

private:

    int port;
    int socketId;
    sockaddr_in sockaddrIn;


    /**
     * initializing the sockaddr_in structure for TCP server setup.
     */
    void initSockaddrIn();

public:

    /**
     * the server constructor getting port number between 1024 to 65536 to bind the server to the port.
     * @param port - int
     * @param stream - std::ostream
     */
    explicit Server(int port);


    /**
     * initializing the server, creating the socket and binding the port.
     * @return  True if success, otherwise false.
     */
    bool initServer();

    /**
     * closing the server socket.
     */
    void closeServer();

    /**
     * listen the server up to n clients.
     * @param n -
     * @return  True if the listen succeed, otherwise False.
     */
    bool listenServer(int n);

    /**
     * getting the socket id number of the server.
     * @return - int
     */
    int getSocketId();

    /**
     * getting the socketAddrIn structure.
     * @return  socketAddr_in structure.
     */
    sockaddr_in getSockaddrIn();

};


#endif //A_OUT_SERVER_H
