//
// Created by oem on 1/16/23.
//
#include "CLI.h"

CLI* CLI::instance = nullptr;
std::string CLI::welcomeMessage = "Welcome to the KNN Classifier Server. Please choose an option:\n";
std::mutex mtx;

CLI::CLI() {

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
    data->metric = "AUC";
    data->k = 5;
    data->trainData = nullptr;
    data->testData = nullptr;
    data->classifiedResult = nullptr;
    data->clientId = clientId;
    data->serverMainIp = serverIp;
}

void *CLI::start(void *data) {
    if(instance == nullptr) {
        // not supposed to happened, but just in case.
        std::cout << "failed starting new client session with client id: " << *(*(ServerData*)data).clientId << std::endl;
        std::cout << "instance variable in CLI class was null\n";
        free((*(ServerData*)data).clientId);
        free((*(ServerData*)data).clientSocket);
        free(data);
        return nullptr;
    }

    /** data is the struct that have:
     * int* clientSocket; malloc
     * int* clientId; malloc
     * std::string* mainServerIp; no need to delete
     */

    // cast the data to serverData type
    int clientId = *(*(ServerData*)data).clientId;
    int clientSocket = *(*(ServerData*)data).clientSocket;
    auto* p_Data = new clientData();

    // initializing the client Data.
    initClientData(p_Data, clientId, (*(ServerData*)data).mainServerIp);

    //releasing memory not in used.
    free((*(ServerData*)data).clientId);
    free((*(ServerData*)data).clientSocket);
    free(data);

    int choice;
    std::cout << "############ Connected to client Socket Number: " << clientSocket <<  " ############" << std::endl;

    // init io and commands:
    SocketIO io(clientSocket);
    UploadFilesServerCommand* uploadFiles = new UploadFilesServerCommand(io);
    AlgorithemSettingServerCommand* algoSetting = new AlgorithemSettingServerCommand(io, 5);
    ClassifyDataServerCommand* classify = new ClassifyDataServerCommand(io);
    DisplayServerCommand* display = new DisplayServerCommand(io);
    DownloadServerCommand* download = new DownloadServerCommand(io);

    // binding the client data with the current thread that handle the client.
    (*(uploadFiles)).p_Data = p_Data;
    (*(algoSetting)).p_Data = p_Data;
    (*(classify)).p_Data = p_Data;
    (*(display)).p_Data = p_Data;
    (*(download)).p_Data = p_Data;

    std::vector<ICommand*> iCommandsVec;
    iCommandsVec.push_back(uploadFiles); // 0
    iCommandsVec.push_back(algoSetting); // 1
    iCommandsVec.push_back(classify); // 2
    iCommandsVec.push_back(display); // 3
    iCommandsVec.push_back(download); // 4

    std::stringstream menu;
    menu << welcomeMessage;
    for (int i = 0; i < COMMAND_SIZE; ++i) {
        menu << iCommandsVec[i]->description;
    }
    menu << "8. exit";
    // inserting the data into the server database.
    instance->serverData.insert({clientId, p_Data});
    std::string userInput;
    while(true) {
        // sending to the client the menu choice
        io.write(menu.str());
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
        if(choice >= 1 && choice <= COMMAND_SIZE) {
            iCommandsVec[choice - 1]->execute();
        }
    }

    // free the client memory data.
    instance->serverData.erase(clientId);
    deleteP_Data(p_Data);
    for(auto & i : iCommandsVec) {
        delete(i);
    }
    return nullptr;
}

void CLI::CliDelete() {

}

void CLI::deleteP_Data(clientData *data) {
    if(data->trainData != nullptr) {
        delete(data->trainData);
    }
    if(data->testData != nullptr) {
        delete(data->testData);
    }
    if(data->classifiedResult != nullptr) {
        delete(data->classifiedResult);
    }
    free(data);
}

