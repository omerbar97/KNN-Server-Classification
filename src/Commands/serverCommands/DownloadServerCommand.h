//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DOWNLOADSERVERCOMMAND_H
#define A_OUT_DOWNLOADSERVERCOMMAND_H

#include <pthread.h>
#include "../ICommand.h"

class DownloadServerCommand : public ICommand{
private:

    static void* newThreadDownload(void* args);

public:
    DownloadServerCommand(DefaultIO &io);

    ~DownloadServerCommand() override;

    void execute() override;

};
#endif //A_OUT_DOWNLOADSERVERCOMMAND_H
