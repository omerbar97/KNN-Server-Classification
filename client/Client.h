//
// Created by oem on 12/23/22.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#ifndef A_OUT_CLIENT_H
#define A_OUT_CLIENT_H
struct Data {
    int data_len;
    char data_addr[];
};

class Client {
private:
    const char* ip_address;
    const int port_no;
    int socket;
    sockaddr_in sin;
    Data data;

public:
    Client(int port_no);


};


#endif //A_OUT_CLIENT_H
