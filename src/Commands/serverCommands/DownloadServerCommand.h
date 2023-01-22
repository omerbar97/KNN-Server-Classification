//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DOWNLOADSERVERCOMMAND_H
#define A_OUT_DOWNLOADSERVERCOMMAND_H
#include <pthread.h>
#include <sys/socket.h>
#include "../ICommand.h"
#include <thread>
#define START_PORT_THREAD 60000
#define PORT_MODULO 500


/**
 * This class is one of the command client can make.
 * which download the classify data.
 */
class DownloadServerCommand : public ICommand{
private:

    static void* newThreadDownload(void* args);

public:
    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
    DownloadServerCommand(DefaultIO &io);

    ~DownloadServerCommand() override;

    void execute() override;

};
#endif //A_OUT_DOWNLOADSERVERCOMMAND_H
