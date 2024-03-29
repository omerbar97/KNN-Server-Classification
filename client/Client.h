//
// Created by oem on 12/23/22.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#define BUFFER_SIZE 4096
#ifndef A_OUT_CLIENT_H
#define A_OUT_CLIENT_H

class Client {
private:
    bool valid;
    const char* ip_address;
    int port_no;
    int socketNum;
    sockaddr_in sin;
    char buffer[BUFFER_SIZE];
    /**
     * Function to initialize Sin correspond to the socket client, return false if there any fail.
     * true otherwise.
     * @return bool.
     */
    bool initSin();

    /**
     * Function to initialize socket;
     * if any fail return false and true otherwise.
     * @return
     */
    bool initSocket();

public:
    /**
    * Constructor that will define the client with the following parameters.
    * @param port_no int.
    * @param ip_address const char*
    * @param stream std::ostream &.
    */
    Client(int port_no, const char* ip_address);


    /**
     * Function that respond to send massages to server.
     * @param data_addr char[].
     * @param data_len int.
     * @return bool.
     */
    bool sendData(char data_addr[] , int data_len);


    /**
     * Function that respond to receive massages to server.
     * @return char*.
     */
    char* readData();

    /**
     * Function that respond to close socket's client.
     * @return int
     */
    void closeSock();

    /**
     * Getter for buffer.
     * @return  getBuffer().
     */
    char* getBuffer();


    /**
     * Getter for valid.
     * @return bool.
     */
    bool getValid();
    /**
     * Getter for socket.
     * @return int.
     */
    int getsocketNum();
};


#endif //A_OUT_CLIENT_H
