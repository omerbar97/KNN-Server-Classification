//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
#define A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H

#include "ServerCommands.h"
#include "../ICommand.h"

class AlgorithemSettingServerCommand : public ICommand , ServerCommands{
private:
    int tokenize(std::string const &str, const char delim,std::vector<std::string> &out);
public:
    int clientId;

    AlgorithemSettingServerCommand(DefaultIO &io);

    ~AlgorithemSettingServerCommand() override;

    void execute() override;

};

#endif //A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
