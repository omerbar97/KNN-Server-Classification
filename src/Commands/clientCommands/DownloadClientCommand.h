//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DOWNLOADCLIENTCOMMAND_H
#define A_OUT_DOWNLOADCLIENTCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"
#include <thread>

/**
 * This class is one of the command client can make.
 */
class DownloadClientCommand : public ICommand {
private:

    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
    explicit DownloadClientCommand(DefaultIO &io);
    /**
     * This function run the download execute just with another thread.
     */
    static void* newThreadDownloadClient(void* args);
public:
    ~DownloadClientCommand() override;
    void execute() override;
private:

};
#endif //A_OUT_DOWNLOADCLIENTCOMMAND_H

