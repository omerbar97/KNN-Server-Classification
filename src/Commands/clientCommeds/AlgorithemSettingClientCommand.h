//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_ALGORITHEMSETTINGCLIENTCOMMAND_H
#define A_OUT_ALGORITHEMSETTINGCLIENTCOMMAND_H

#include "../ICommand.h"
#include "../../../client/Client.h"

class AlgorithemSettingClientCommand : public ICommand {
public:
    AlgorithemSettingClientCommand(DefaultIO &io);
    void execute() override;
private:

};

#endif //A_OUT_ALGORITHEMSETTINGCLIENTCOMMAND_H