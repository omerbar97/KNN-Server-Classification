//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DOWNLOADCLIENTCOMMAND_H
#define A_OUT_DOWNLOADCLIENTCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"


class DownloadClientCommand : public ICommand {
public:
    DownloadClientCommand(DefaultIO &io);
    ~DownloadClientCommand() override;
    void execute() override;
private:

};
#endif //A_OUT_DOWNLOADCLIENTCOMMAND_H

