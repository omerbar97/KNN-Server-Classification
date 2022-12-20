//
// Created by omer on 12/21/22.
//
#include "../calculate/input.h"
#include <fstream>
#include "Server.h"
#include "../calculate/Algorithim/Knn.h"

bool isArgsServerInputValid(char* args[]) {
    // looking at args[1] should be the file_name or file_path:
    // trying the open the file with not added path:
    std::fstream file(args[1], std::ios::in);
    if(!file.is_open()) {
        // adding the relative path:
        std::string fileName = args[1];
        std::string filePath = "../resources/datasets/" + fileName;
        std::fstream file2(filePath, std::ios::in);
        if(!file2.is_open()) {
            return false;
        }
    }
    // checking port input:
    int port, counter = 0;
    try {
        port = std::atoi(args[2]);
    }
    catch(std::exception const &e) {
        return false;
    }
    // checking if the port is only 4 digis.
    while(port > 0) {
        counter++;
        port /= 10;
    }
    if(counter != 4) {
        return false;
    }
    return true;
}

int main(int argc, char *args[]) {
    // in args: <server.out> <file(name or path)> <int port>
    if(argc != 3 || !isArgsServerInputValid(args)) {
        input::error();
    }
    int port = std::atoi(args[2]);

    // creating the server instance:
    Server tcpServer(port, std::cout);

    // initializing the server:
    if(!tcpServer.initServer()) {
        // failed initializing.
        exit(1);
    }




    tcpServer.closeServer();
    return 0;
}