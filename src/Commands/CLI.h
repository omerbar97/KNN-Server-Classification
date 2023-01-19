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
#include "serverCommands/EndingConnection.h"


#include <map>
#include <mutex>
#include "ICommand.h"
#include "../Algorithim/Knn.h"
#include "../../server/Server.h"
#define BUFFER_SIZE 4096



class CLI {
private:
    static CLI* instance;
    CLI();

public:
    ~CLI();

    std::map<int, clientData*> serverData;

    static CLI& getInstance();

    static void* start(void * data);

    static void CliDelete();
};

#endif //A_OUT_CLI_H
