//
// Created by omer on 12/21/22.
//
#include "../src/input.h"
#include "stdlib.h"
#include <fstream>
#include "Server.h"
#include "../src/Algorithim/Knn.h"
#include "../src/Commands/clientCommands/AlgorithemSettingClientCommand.h"
#include "../src/Commands/clientCommands/ClassifyDataClientCommand.h"
#include "../src/Commands/ICommand.h"
#include "../src/IO/SocketIO.h"
#include <pthread.h>
#include "../src/Commands/ICommand.h"
#include "../src/IO/DefaultIO.h"
#include "../src/IO/SocketIO.h"
#include "../src/IO/FileIO.h"
#include "../src/IO/StandardIO.h"
#include "../src/Commands/serverCommands/UploadFilesServerCommand.h"

#define BUFFER_SIZE 4096

struct ServerData{
    int* clientSocket;
    int* clientId;
    Server* server;
};

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

/**
 * getting the input from the client in the form of <vector> <distance> <int k> and checking the input by all the parameters.
 * if all the input is correct then returning an vector of size 3 of string.
 * at index 0 - the string vector.
 * at index 1 - the distance string.
 * at index 2 - the integer k.
 * @param input - arrays of char in the size 4096
 * @return - std::vector<string>
 */
std::vector<std::string> getClientInputVector(char input[BUFFER_SIZE]) {
    // client data is in the form <vector> <distance> <int k>
    std::string temp(input);
    std::vector<std::string> result;
    std::size_t distancePos = -1;
    if(temp.find("MAN") != std::string::npos) {
        distancePos = temp.find("MAN");
    }
    else if(temp.find("AUC") != std::string::npos) {
        distancePos = temp.find("AUC");
    }
    else if(temp.find("CHB") != std::string::npos) {
        distancePos = temp.find("CHB");
    }
    else if(temp.find("CAN") != std::string::npos) {
        distancePos = temp.find("CAN");
    }
    else if(temp.find("MIN") != std::string::npos) {
        distancePos = temp.find("MIN");
    }
    if(distancePos == -1) {
        // error returning empty vector.
        return {};
    }
    // getting the all the vector elements.
    std::string vector(temp.substr(0, distancePos - 1));
    // getting the distance name.
    std::string distance(temp.substr(distancePos, 3));
    // getting all the information after distance name.
    temp = temp.substr(distancePos + 4);

    result.push_back(vector);
    result.push_back(distance);
    result.push_back(temp);

    // result vector should look like that: <vector> <distance> <int k>

    return result;
}

std::string retrieveFilePath(std::string fileName, int flag) {
    std::string path;
    if(flag == 1) {
        // 1 - the file path is relative (only name)
        path = "../resources/datasets/" + fileName;
    }
    else {
        // 2 - the file name is a full path.
        path = fileName;
    }
    return path;
}

/**
 * calculating the client input, given the buffer input got from the client and reference to knn algorithm, separating the
 * buffer input into 3:
 * 1. vector
 * 2. distance
 * 3. integer k
 * returning the result classified of the vector with the given algorithm, file, integer k.
 * @param buffer - char arrays size 4096
 * @param knn - the knn algorithm.
 * @return if the input is correct. returning the classified result from the knn, otherwise returning empty object.
 */
std::string calculateClientInput(char buffer[BUFFER_SIZE], Knn& knn) {
    // vector DISTANCE K
    std::vector<std::string> vInput = getClientInputVector(buffer);
    if(vInput.empty()) {
        // error invalid input returning empty string.
        return {};
    }

    // client data is in the form <vector> <distance> <int k>
    // vInput[0] - vectors string
    // vInput[1] - distance string
    // vInput[2] - k.

    int k;
    Distance* distance = nullptr;
    std::vector<std::string> vString;
    vString = input::splitString(vInput[0]);

    std::vector<double> vDouble;
    try{
        vDouble = input::convertStrVecToDoubleVec(vString);
        k = std::stoi(vInput[2]);
    }
    catch(std::invalid_argument &argument) {
        return {};
    }
    // checking the input of the Vector<double>
    if(vDouble.empty()) {
        return {};
    }
    distance = input::getDistance(vInput[1]);
    if(distance == nullptr) {
        return {};
    }

    knn.setDistance(distance);
    knn.setK(k);
    knn.setVector(vDouble);

    knn.calculate();

    delete(distance);
    knn.setDistance(nullptr);

    return knn.getClassified();
}

//ICommand** initCommands(Server* server, int clientSocket) {
//    // first command
//    SocketIO io(clientSocket);
//    ICommand** pCommand = (ICommand**)malloc(sizeof(ICommand)*1);
//    ICommand* command = new UploadFilesCommand("1. uploading files to server\n", io, *server);
//    pCommand[0] = command;
//    return pCommand;
//}

void deleteCommands(ICommand** pCommand, int size) {
    for(int i = 0; i < size; i++) {
        delete(pCommand[i]);
    }
}


void* handleConnection(void* data) {
    // handle all the client connection with the server
    int fails = 0;
    char buffer[BUFFER_SIZE];
    std::string menu = "1. uploading files to the server\n"
                       "2. change algorithm settings\n"
                       "3. classifying the data\n"
                       "4. display result\n"
                       "5. writing result to file\n"
                       "8. ending connection.\n";
    char bufferToSend[BUFFER_SIZE];
    ServerData* d = (ServerData*)data;
    int clientSocket = *((int*)d->clientSocket);
    Server* server = d->server;
    int readBytes, sendBytes,choice;
    std::cout << "###-------------Connected to client-------------###" << std::endl;
    std::cout << "-------------Client Port Number: " << clientSocket << std::endl;
    SocketIO io(clientSocket);
    UploadFilesServerCommand uploadFiles(io, *d->clientId);
    UploadFilesServerCommand uploadFiles(io);

    while(true) {
        // sending the client the menu choice
        strcpy(buffer, menu.c_str());
        sendBytes = send(clientSocket, buffer, BUFFER_SIZE, 0);
        if(sendBytes < 0) {
            perror("failed sending menu to client");
            fails++;
            if(fails > 10) {
                // max fails connection
                perror("failed sending to client to many times");
                break;
            }
            continue;
        }
        // waiting to client.
        readBytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if(readBytes == 0) {
            // the socket with client was closed.
            std::cout << "the connection with client_socket_number: " << clientSocket << "was closed" << std::endl;
            break;
        }
        else if(readBytes < 0) {
            perror("failed receiving data from the client");
            continue;
        }
        else {
            // client has 6 options:
            /**
             * 1. uploading files to the server
             * 2. change algorithm settings
             * 3. classifying the data
             * 4. display result
             * 5. writing result to file
             * 8. ending connection.
             */
             std::cout << "Message from client: " << buffer << std::endl;
            // calling the call command.
        }
        choice = std::atoi(&buffer[0]);
        if(choice == 0) {
            // invalid input.. print message and return to loop
            continue;
        }
        switch (choice) {
            case 1:
                uploadFiles.execute();
                break;
            case 2:


            case 3:


            case 4:


            case 5:


            case 8:

                break;
        }
        fails = 0;
    }
    free(d->clientSocket);
    free(d->clientId);
    free(d);
    return NULL;
}

int main(int argc, char *args[]) {

    // in args: <server.out> <file(name or path)> <int port>
//    int flag = isArgsServerInputValid(args);
    // in case flag is equal to:
    // 0 - incorrect input.
    // 1 - the file path is relative (only name)
    // 2 - the file path is a full path.
//    if(argc != 3 || isArgsServerInputValid(args) == 0) {
//        std::cout <<"Invalid argument input, please make sure you execute the program as follow:\n"
//                  << "./server.out <file name/full_path> <server_port>\n"
//                  << "for example: ./server.out iris_classified.csv 12345\n"
//                  << "Make sure the port number is between 1024 to 65536 and that the file name/path is case sensitive.\n";
//        exit(1); // input exit code 1
//    }

    //std::string filePath = retrieveFilePath(args[1], flag);

    // input already check no need for try and catch.
    int port = std::atoi(args[2]);

    // creating the server instance:
    Server tcpServer(port);
    // ICommand[] *commands = {AlgorithemSettingCommand() , ClassifyDataCommand(SocketIO())} ;
    Server* mainServer = new Server(port);

    // initializing the server:
    if(!mainServer->initServer()) {
        // failed initializing.
        exit(2); // server exit code 2
    }

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int clientSocket;
    int readBytes;
    int sendBytes;

    std::cout << "-------------Server Socket number: " << mainServer->getSocketId() << std::endl;
    std::cout << "-------------Server Port number: " << mainServer->getSockaddrIn().sin_port << std::endl;

    if(!mainServer->listenServer(5)){
        perror("failed listening to the socket");
        exit(1);
    }
    while(true) {
        clientSocket = accept(mainServer->getSocketId(), (struct sockaddr *) &client_sin, &addr_len);
        if(clientSocket < 0) {
            perror("failed connecting the client");
            // connecting to other clients.
            continue;
        }
        ServerData *args = (ServerData*)malloc(sizeof(ServerData));
        args->clientSocket = (int*)malloc(sizeof(int));
        args->clientId = (int*)malloc(sizeof(int));
        *args->clientSocket = clientSocket;
        args->server = mainServer;
        pthread_t tid;
        pthread_create(&tid, NULL, handleConnection, (void*)args);
    }
    mainServer->closeServer();
    return 0;
}