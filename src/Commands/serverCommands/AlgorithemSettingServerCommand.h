//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
#define A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
#include <string>
#include <sstream>
#include <sstream>
#include "ServerCommands.h"
#include "../ICommand.h"

class AlgorithemSettingServerCommand : public ICommand{

private:
    int tokenize(std::string const &str, const char delim,std::vector<std::string> &out);

public:
    AlgorithemSettingServerCommand(DefaultIO &io, int k);

    ~AlgorithemSettingServerCommand() override;

    void execute() override;

};

#endif //A_OUT_ALGORITHEMSETTINGSERVERCOMMAND_H
