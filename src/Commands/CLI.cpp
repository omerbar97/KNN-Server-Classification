//
// Created by oem on 1/16/23.
//
#include "CLI.h"

CLI* CLI::instance = NULL;
std::string CLI::menu = "Welcome to the KNN Classifier Server. Please choose an option:\n"
                        "1. upload an unclassified csv data file\n"
                        "2. algorithm settings\n"
                        "3. classify data\n"
                        "4. display results\n"
                        "5. download results\n"
                        "8. exit";;
std::mutex mtx;
CLI::CLI(){
    // init commands

}
CLI::~CLI(){

}

CLI &CLI::getInstance() {
    mtx.lock();
    if(instance == NULL) {
        instance = new CLI();
    }
    mtx.unlock();
    return *instance;
}
void initClientData(clientData * data) {
    data->metric = "EUC";
    data->k = 5;
    data->testData = {};
    data->trainData = {};
}

void *CLI::start(void *data) {
    // data is struct that have:
    // 1.clientId
    // 2.clientSocket
    // 3.clientData strcuture

    // cast the data to serverData type
    int clientId = (*(ServerData*)data).clientId;
    int clientSocket = (*(ServerData*)data).clientSocket;
    clientData* p_Data = (clientData*)malloc(sizeof(clientData));
    //init p_Data
    initClientData(p_Data);

    // check if malloc works
    std::cout << p_Data->metric << " " <<  p_Data->k;
    free(data);

<<<<<<< HEAD
=======

>>>>>>> fa18f4bf7798c9f8dbb6af1d68de00da52154ac7
    int readBytes, sendBytes,choice, fails = 0;
    char buffer[BUFFER_SIZE];
    std::cout << "###-------------Connected to client-------------###" << std::endl;
    std::cout << "-------------Client Port Number: " << clientSocket << std::endl;

    // init io and commands:
    SocketIO io(clientSocket);
    UploadFilesServerCommand uploadFiles(io);
    AlgorithemSettingServerCommand algoSetting(io, 5);
    ClassifyDataServerCommand classify(io);
    DisplayServerCommand display(io);
    DownloadServerCommand download(io);
    EndingConnection exit(io);


    uploadFiles.p_Data = p_Data;
    algoSetting.p_Data = p_Data;
    classify.p_Data = p_Data;
    display.p_Data = p_Data;
    exit.p_Data = p_Data;

    std::vector<ICommand*> iCommandsVec;
    iCommandsVec.push_back(&uploadFiles);
    iCommandsVec.push_back(&uploadFiles);
    iCommandsVec.push_back(&algoSetting);
    iCommandsVec.push_back(&classify);
    iCommandsVec.push_back(&display);
    iCommandsVec.push_back(&download);
    iCommandsVec.push_back(&exit);
    iCommandsVec.push_back(&exit);
    iCommandsVec.push_back(&exit);

    std::stringstream menu;
    for (int i = 1; i < 7; ++i) {
        menu << iCommandsVec[i]->description;
    }

    instance->serverData.insert({clientId, p_Data});

    while(true) {
        // sending the client the menu choice
        strcpy(buffer, menu.str().c_str());
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
        else if(strcmp(buffer, "-1") == 0) {
            //invalid input from client, send again menu
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

        //going to the correct position in the vector
        if((choice >= 0 && choice <= 5) || choice == 8) {
            iCommandsVec[choice]->execute();
        }

        fails = 0;
    }
    // free the client memory data.
    free(p_Data);
    return NULL;
}

void CLI::CliDelete() {
    delete(instance);
}

