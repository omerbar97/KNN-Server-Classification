//
// Created by omer on 12/21/22.
//
#include "../src/input.h"
#include "stdlib.h"
#include "Server.h"
#include "../src/Algorithim/Knn.h"
#include "../src/Commands/clientCommands/AlgorithemSettingClientCommand.h"
#include "../src/Commands/clientCommands/ClassifyDataClientCommand.h"
#include "../src/Commands/CLI.h"
#include <pthread.h>
#include "../src/IO/StandardIO.h"
#define BUFFER_SIZE 4096
#define LEGAL_SERVER_START_PORT 1024
#define LEGAL_SERVER_END_PORT 59999

static int globalClientId = 0;

/**
 * checking if the server arguments are valid.
 * @param args - program argument.
 * @return - 0 if arguments are invalid, 1 if arguments valid and the path is relative,
 * 2 if the arguments valid and the file is only name.
 */
int isArgsServerInputValid(char* args[]) {

    // looking at args[1] should be the file_name or file_path:
    // trying the open the file with not added path:
    std::fstream file(args[1], std::ios::in);
    int flag = 0;
    if(!file.is_open()) {
        // adding the relative path:
        std::string fileName = args[1];
        std::string filePath = "../resources/datasets/" + fileName;
        std::fstream file2(filePath, std::ios::in);
        if(!file2.is_open()) {
            return flag;
        }
        file2.close();
        flag = 1;     // relative path (name only)
    }
    else {
        file.close(); // closing the file
        flag = 2;     // full path
    }
    // checking port input:
    int port, i = 0;
    port = std::atoi(args[2]);
    while(args[2][i] != '\0') {
        i++;
    }
    // function atoi transforming string to int but if the string is 1234a5 the atoi returns 1234 then we check if the
    // last digit is the same as the port result.
    if(port == 0 || port % 10 != args[2][i - 1] - '0') {
        return 0;
    }
    // checking if the port is only 4 digis.
    if(!(port >= 1024 && port <= 65536)) {
        return 0; // error
    }
    return flag;
}


void deleteCommands(ICommand** pCommand, int size) {
    for(int i = 0; i < size; i++) {
        delete(pCommand[i]);
    }
}

bool checkPort(int port) {
    if(port >= LEGAL_SERVER_START_PORT && port <= LEGAL_SERVER_END_PORT) {
        return true;
    }
    return false;
}



int main(int argc, char *args[]) {

    // in args: <server.out> <int port>

    // input already check no need for try and catch.
    int port = std::atoi(args[1]);

    if(!checkPort(port) || argc != 2){
        // incorrect port
        std::cout << "Invalid arguments input, please make sure you start program as follow:\n"
                     "./server.out <port number>\n"
                     "without the \"<\",\">\" and port number must be over 1024 and less then 60000\n";
        exit(1);
    }

    // creating the server instance:
    auto* mainServer = new Server(port);

    // initializing the server:
    if(!mainServer->initServer()) {
        // failed initializing.
        std::cout << "failed initializing server, please wait a few minutes and start again\n";
        delete(mainServer);
        exit(1); // server exit code 2
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int clientSocket;

    //printing to server
    std::cout << "-------------Main Server Socket number: " << mainServer->getSocketId() << " -------------" << std::endl;
    std::cout << "-------------Main Server Port number: " << mainServer->getSockaddrIn().sin_port << " -------------" << std::endl;

    if(!mainServer->listenServer(10)){
        perror("failed listening to the socket");
        delete(mainServer);
        exit(1);
    }

    // localhost server port.
    auto* serverIp = new std::string("127.0.0.1");
    // creating CLI class to handle all clients.
    CLI cli = CLI::getInstance(); // getting the singleton instance. allocated in the heap.
    while(true) {
        clientSocket = accept(mainServer->getSocketId(), (struct sockaddr *) &client_sin, &addr_len);
        if(clientSocket < 0) {
            perror("failed connecting the client");
            // connecting to other clients.
            continue;
        }
        if(globalClientId == 1) {
            std::cout << "Test";
        }

        // creating the struct to pass the server information to the client.
        auto *arguments = new ServerData();

        arguments->clientId = (int*)malloc(sizeof(int));
        if(arguments->clientId == nullptr) {
            perror("failed allocating memory for client");
            delete(arguments);
            continue;
        }

        arguments->clientSocket = (int*)malloc(sizeof(int));
        if(arguments->clientSocket == nullptr) {
            perror("failed allocating memory for client");
            free(arguments->clientId);
            delete(arguments);
            continue;
        }

        // setting unique client id.
        *(arguments->clientId) = globalClientId++;
        *(arguments->clientSocket) = clientSocket;
        arguments->mainServerIp = serverIp;

        // creating new thread to handle the client.
        pthread_t tid;
        pthread_create(&tid, nullptr, CLI::start, (void*)arguments);
    }
    // deleting resources:
    for(int i = 0; i < globalClientId; i++) {
        clientData* d = CLI::getInstance().serverData.at(i);
        if(d != nullptr) {
            delete(d->classifiedResult);
            delete(d->testData);
            delete(d->trainData);
            delete(d);
        }
    }
    delete(serverIp);
    delete(mainServer);
    CLI::CliDelete();
    mainServer->closeServer();
    return 0;
}