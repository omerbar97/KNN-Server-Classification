//
// Created by oem on 1/16/23.
//

#ifndef A_OUT_CLI_H
#define A_OUT_CLI_H
#include <iostream>
#include "../IO/SocketIO.h"
#include "serverCommands/UploadFilesServerCommand.h"
#include "serverCommands/AlgorithemSettingServerCommand.h"
#include "serverCommands/ClassifyDataServerCommand.h"
#include "serverCommands/DisplayServerCommand.h"
#include "serverCommands/DownloadServerCommand.h"
#include <map>
#include <mutex>
#include "ICommand.h"
#include "../Algorithim/Knn.h"
#include "../../server/Server.h"
#define BUFFER_SIZE 4096
#define COMMAND_SIZE 5
#define NUMBER_OF_FAILS 10


/**
 * This class is a singleton this instance hold the information of all clients.
 * The server use in this data.
 */
class CLI {
private:
    static CLI* instance;
    static std::string welcomeMessage;
    CLI();

public:
    ~CLI();

    std::map<int, clientData*> serverData;
/**
 * Function that return the one instance(depend if the instance is already initialized or not).
 * We update in lock in the condition of if the instance is already initialized for handle cases tht we work with some threads.
 * @return CLI& , instance of CLI.
 */
    static CLI& getInstance();
/**
 * This function used to open a new client in the server, so the server start to work with him.
 * handle with  the logic's of how to work with the input the client given to the server.
 * @param data , pointer to the struct- (1)int - client id (2)int - clientSocket (3)clientData* (struct in DataStructs)
 * @return void*.
 */
    static void* start(void * data);

    static void CliDelete();
/**
 * Function to delete all data for the specific client the we allocate in the heap.
 * @param data ,pointer to the struct- (1)int - client id (2)int - clientSocket (3)clientData* (struct in DataStructs)
 */
    static void deleteP_Data(clientData* data);
};

#endif //A_OUT_CLI_H
