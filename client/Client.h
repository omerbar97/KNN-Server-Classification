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
    int port_no;
    int socketNum;
    sockaddr_in sin;
    char buffer[4096];
    bool initSin();
    bool initSocket();

public:
    Client(int port_no, const char* ip_address);
    Data getData();
    bool SendData(char data_addr[] , int data_len);
    char* readData();
    int closeSock();



};


#endif //A_OUT_CLIENT_H
