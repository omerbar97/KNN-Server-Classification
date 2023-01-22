//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_CLASSIFYDATASERVERCOMMAND_H
#define A_OUT_CLASSIFYDATASERVERCOMMAND_H

#include "../ICommand.h"
#include "../CLI.h"
#include "../../IO/DefaultIO.h"
#include <map>
/**
 * This class is one of the command client can make.
 * which adk the server to classify the data.
 */
class ClassifyDataServerCommand : public ICommand{

public:

    std::map<int, clientData> serverData;
    int clientId;
    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
    ClassifyDataServerCommand(DefaultIO &io);

    ~ClassifyDataServerCommand() override;

    void execute() override;

};
#endif //A_OUT_CLASSIFYDATASERVERCOMMAND_H
