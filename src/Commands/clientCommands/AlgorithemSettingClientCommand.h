//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_ALGORITHEMSETTINGCLIENTCOMMAND_H
#define A_OUT_ALGORITHEMSETTINGCLIENTCOMMAND_H
#include "../../../client/Client.h"
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"

/**
 * This class is one of the command client can make.
 */
class AlgorithemSettingClientCommand : public ICommand {
public:
    /**
     * constructor that get the IO(connection between client to server).
     * @param io
     */
    AlgorithemSettingClientCommand(DefaultIO &io);
    void execute() override;
    ~AlgorithemSettingClientCommand() override;
private:

};

#endif //A_OUT_ALGORITHEMSETTINGCLIENTCOMMAND_H
