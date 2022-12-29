#include "Client.h"
#include <fstream>
#include <iostream>
#include "../calculate/input.h"
#define IP_SIZE 15
#define BUFFER_SIZE 4096
//255.255.255.255
bool isPort(const char *port) {

    int x;
    x = atoi(port);
    if(x >= 1024 && x < 65536) {
        return true;
    }
    return false;
}
/**
 * BUGSSS need TO FIX!
 * @param ip
 * @return
 */
bool isIp(const char *ip) {
    char *ptr = (char*)malloc(sizeof(ip)*IP_SIZE + 1);
    if(ptr == NULL) {
        return false;
    }
    memcpy(ptr, ip, IP_SIZE);
    int counter = 0;
    ptr = strtok(ptr,".");
    while (ptr != NULL) {
        counter++;
        if(atoi(ptr) == 0 && *ptr != '0') {
            free(ptr);
            return false;
        }
        atoi(ptr);
        ptr = strtok(NULL,".");
    }
    if(counter == 4) {
        free(ptr);
        return true;
    }
    free(ptr);
    return false;
}
bool userAskToClose(std::string str) {
    try {
        if (atoi(str.c_str()) == -1) {
            return true;
        }
    }
    catch (std::exception d) {
        return false;
    }
    return false;
}
char* strToChrArray(std::string s) {
    char * data = new char [s.size()];
    for(int i = 0 ; i < s.size() ; i++) {
        data[i] = s[i];
    }
    return data;
}


int main(int argc, char *args[]) {
    bool isOn = true;
    std::string userInput;
    if(argc != 3 || !isPort(args[2]) || !isIp(args[1])) {
        std::cout<<"Invalid argument input!" << std::endl;
        return 0;
    }
    //otherwise, the input is correct.
    const char* ip_address = args[1];
    int port_no = atoi(args[2]);

    //initializing  Client.
    Client client(port_no, ip_address, std::cout);
    if(!client.isValid()) {
        input::print("Failed to initializing the client.", client.getStream());
        exit(1);
    }
    //looping and sending message from client to server until client send -1.
    while (isOn) {
        std::getline(std::cin, userInput);
        if(userAskToClose(userInput)) {
            //exit from the loop and close socket.
            client.closeSock();
            isOn = false;
            break;
        }
        //otherwise, send the data to server.
        char *data = strToChrArray(userInput);
        client.SendData(data, BUFFER_SIZE);
        client.readData();
        input::print("Server send: " , client.getStream(), "");
        input::print(client.getBuffer(), client.getStream());
    }
    return 0;
}