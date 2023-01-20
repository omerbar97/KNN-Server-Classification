//
// Created by oem on 1/16/23.
//
#include "CLI.h"

CLI* CLI::instance = nullptr;
std::string CLI::welcomeMessage = "Welcome to the KNN Classifier Server. Please choose an option:\n";

std::mutex mtx;
CLI::CLI(){
    // init commands

}
CLI::~CLI(){

}

CLI &CLI::getInstance() {
    mtx.lock();
    if(instance == nullptr) {
        instance = new CLI();
    }
    mtx.unlock();
    return *instance;
}
void initClientData(clientData * data, int clientId, std::string* serverIp) {
    data->metric = "EUC";
    data->k = 5;
    data->testData = {};
    data->trainData = {};
    data->clientId = clientId;
    data->serverMainIp = serverIp;
}

void *CLI::start(void *data) {
    // data is struct that have:
    // 1.clientId
    // 2.clientSocket
    // 3.clientData strcuture

    // cast the data to serverData type
    int clientId = *(*(ServerData*)data).clientId;
    int clientSocket = *(*(ServerData*)data).clientSocket;
    auto* p_Data = (clientData*)malloc(sizeof(clientData));
    //init p_Data
    if(clientId == 1) {
        std::cout <<"test";
    }
    initClientData(p_Data, clientId, (*(ServerData*)data).mainServerIp);


    // check if malloc works
    free((*(ServerData*)data).clientId);
    free((*(ServerData*)data).clientSocket);
    free(data);

    int choice, fails = 0;
    char buffer[BUFFER_SIZE];
    std::cout << "############ Connected to client Socket Number: " << clientSocket <<  " ############" << std::endl;

    // init io and commands:
    SocketIO io(clientSocket);
    UploadFilesServerCommand* uploadFiles = new UploadFilesServerCommand(io);
    AlgorithemSettingServerCommand* algoSetting = new AlgorithemSettingServerCommand(io, 5);
    ClassifyDataServerCommand* classify = new ClassifyDataServerCommand(io);
    DisplayServerCommand* display = new DisplayServerCommand(io);
    DownloadServerCommand* download = new DownloadServerCommand(io);
    EndingConnection* exit = new EndingConnection(io);

    // binding the client data with the current thread that handle the client.
    (*(uploadFiles)).p_Data = p_Data;
    (*(algoSetting)).p_Data = p_Data;
    (*(classify)).p_Data = p_Data;
    (*(display)).p_Data = p_Data;
    (*(download)).p_Data = p_Data;
    (*(exit)).p_Data = p_Data;

    std::vector<ICommand*> iCommandsVec;
    iCommandsVec.push_back(uploadFiles); // 0
    iCommandsVec.push_back(algoSetting); // 1
    iCommandsVec.push_back(classify); // 2
    iCommandsVec.push_back(display); // 3
    iCommandsVec.push_back(download); // 4
    iCommandsVec.push_back(exit); // 5

    std::stringstream menu;
    menu << welcomeMessage;
    for (int i = 0; i < 6; ++i) {
        menu << iCommandsVec[i]->description;
    }

    instance->serverData.insert({clientId, p_Data});
    std::string userInput;
    while(true) {
        // sending the client the menu choice
        io.write(menu.str());
        if(!io.isValid()) {
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
        userInput = io.read();
        if(!io.isValid()) {
            perror("failed receiving data from the client");
            continue;
        }
        else if(userInput == "8") {
            // the socket with client was closed.
            std::cout << "the connection with client_socket_number: " << clientSocket << " was closed." << std::endl;
            break;
        }
        else if(userInput == "-1") {
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
            std::cout << "Message from client-Socket-Number-" << clientSocket << ": " << userInput << std::endl;
            // calling the call command.
        }
        choice = std::atoi(userInput.c_str());

        //going to the correct position in the vector
        if(choice >= 1 && choice <= 5) {
            iCommandsVec[choice - 1]->execute();
        }
        fails = 0;
    }
    // free the client memory data.
    instance->serverData.erase(clientId);
    free(p_Data);
    for(auto & i : iCommandsVec) {
        delete(i);
    }
    return nullptr;
}

void CLI::CliDelete() {
    delete(instance);
}


