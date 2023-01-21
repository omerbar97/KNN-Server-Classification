//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DOWNLOADCLIENTCOMMAND_H
#define A_OUT_DOWNLOADCLIENTCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"
#include <thread>


class DownloadClientCommand : public ICommand {
private:

    static void* newThreadDownloadClient(void* args);


public:
    explicit DownloadClientCommand(DefaultIO &io);
    ~DownloadClientCommand() override;
    void execute() override;
private:

};
#endif //A_OUT_DOWNLOADCLIENTCOMMAND_H

