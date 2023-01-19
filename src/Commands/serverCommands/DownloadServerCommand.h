//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DOWNLOADSERVERCOMMAND_H
#define A_OUT_DOWNLOADSERVERCOMMAND_H


#include "../ICommand.h"

class DownloadServerCommand : public ICommand{

public:
    DownloadServerCommand(DefaultIO &io);

    ~DownloadServerCommand() override;

    void execute() override;

};
#endif //A_OUT_DOWNLOADSERVERCOMMAND_H
