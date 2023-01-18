//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_CLASSIFYDATASERVERCOMMAND_H
#define A_OUT_CLASSIFYDATASERVERCOMMAND_H

#include "../ICommand.h"
#include "../CLI.h"
#include "../../IO/DefaultIO.h"
#include "../../../src/Algorithim/CSVStruct.h"
#include "ServerCommands.h"
class ClassifyDataServerCommand : public ICommand , ServerCommands{

public:
    int clientId;

    ClassifyDataServerCommand(DefaultIO &io, int clientId);

    ~ClassifyDataServerCommand() override;

    void execute() override;

};
#endif //A_OUT_CLASSIFYDATASERVERCOMMAND_H
