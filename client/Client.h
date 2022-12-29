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
    bool valid;
    const char* ip_address;
    std::ostream& stream;
    int port_no;
    int socketNum;
    sockaddr_in sin;
    char buffer[4096];
    bool initSin();
    bool initSocket();

public:

    Client(int port_no, const char* ip_address, std::ostream &stream);
    bool SendData(char data_addr[] , int data_len);
    char* readData();
    int closeSock();
    char* getBuffer();
    std::ostream& getStream();
    bool isValid();



};


#endif //A_OUT_CLIENT_H
