//
// Created by omer on 12/21/22.
//
#include "../calculate/input.h"
#include <fstream>
#include "Server.h"
#include "../calculate/Algorithim/Knn.h"

#define BUFFER_SIZE 4096

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
        return 0; // error
    }
    return flag;
}

std::vector<std::string> getClientInputVector(char input[BUFFER_SIZE]) {
    // client data is in the form <vector> <distance> <int k>
    std::string temp(input);
    std::vector<std::string> result;
    std::size_t distancePos = 0;
    if((distancePos = temp.find("MAN")) > 0);
    else if((distancePos = temp.find("AUC")) > 0);
    else if((distancePos = temp.find("CHB")) > 0);
    else if((distancePos = temp.find("CAN")) > 0);
    else if((distancePos = temp.find("MIN")) > 0);
    if(distancePos == -1) {
        // error returning empty vector.
        return result;
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

std::string calculateClientInput(char buffer[BUFFER_SIZE], Knn& knn) {

    std::vector<std::string> vInput = getClientInputVector(buffer);
    if(vInput.empty()) {
        // error invalid input returning empty string.
        std::string n;
        return n;
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
        std::string n;
        return n;
    }
    // checking the input of the Vector<double>
    if(vDouble.empty()) {
        std::string n;
        return n;
    }
    distance = input::getDistance(vInput[1]);
    if(distance == nullptr) {
        std::string n;
        return n;
    }

    knn.setDistance(distance);
    knn.setK(k);
    knn.setVector(vDouble);

    knn.calculate();

    delete(distance);
    knn.setDistance(nullptr);

    return knn.getClassified();
}

int main(int argc, char *args[]) {
    // in args: <server.out> <file(name or path)> <int port>
    int flag = isArgsServerInputValid(args);
    // in case flag is equal to:
    // 0 - incorrect input.
    // 1 - the file path is relative (only name)
    // 2 - the file path is a full path.
    if(argc != 3 || isArgsServerInputValid(args) == 0) {
        input::error();
        exit(1); // input exit code 1
    }

    std::string filePath = retrieveFilePath(args[1], flag);

    // input already check no need for try and catch.
    int port = std::atoi(args[2]);

    // creating the server instance:
    Server tcpServer(port, std::cout);

    // initializing the server:
    if(!tcpServer.initServer()) {
        // failed initializing.
        exit(2); // server exit code 2
    }

    ReadCSV fileCSV(filePath, tcpServer.getStream());

    Knn knn(fileCSV.getData());

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int clientSocket;
    int readBytes;
    int sendBytes;


    // server loop. -----------------------------------------------------------------
    while(true) {
        if(tcpServer.listenServer(5) < 0){
            input::print("failed listening to the socket.",  tcpServer.getStream());
        }
        // waiting to client.
        clientSocket = accept(tcpServer.getSocketId(), (struct sockaddr *) &client_sin, &addr_len);
        if(clientSocket < 0) {
            input::print("failed connecting the client", tcpServer.getStream());
        }
        char buffer[BUFFER_SIZE];
        readBytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if(readBytes == 0) {
            // empty message;
            input::error();
        }
        else if(readBytes < 0) {
            input::print("failed receiving data from the client.", tcpServer.getStream());
        }
        else {

            // client data is in the form <vector> <distance> <int k>
            // input[0] - vectors string
            // input[1] - distance string
            // input[2] - k.
            std::string classifiedToPrint = calculateClientInput(buffer, knn);
            char bufferToSend[BUFFER_SIZE];
            if(classifiedToPrint.empty()) {
                // error invalid input.
                input::error(tcpServer.getStream());
                std::strcpy(bufferToSend, "invalid input");
            }
            else {
                input::print("In Server: ", tcpServer.getStream(), knn.getClassified() + "\n");
                std::strcpy(bufferToSend, knn.getClassified().c_str());
            }
            // sending the data.
            sendBytes = send(clientSocket, bufferToSend, readBytes, 0);
            if(sendBytes < 0) {
                input::print("failed to send data to the client.", tcpServer.getStream());
            }
        }
    }
    tcpServer.closeServer();
    return 0;
}