//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_CLASSIFYDATASERVERCOMMAND_H
#define A_OUT_CLASSIFYDATASERVERCOMMAND_H

#include "../ICommand.h"
#include "../CLI.h"
#include "../../IO/DefaultIO.h"
#include <map>

class ClassifyDataServerCommand : public ICommand{

public:

    std::map<int, clientData> serverData;
    int clientId;

    ClassifyDataServerCommand(DefaultIO &io);

    ~ClassifyDataServerCommand() override;

    void execute() override;

};
#endif //A_OUT_CLASSIFYDATASERVERCOMMAND_H
