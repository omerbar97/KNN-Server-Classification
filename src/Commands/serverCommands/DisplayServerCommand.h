//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DISPLAYSERVERCOMMAND_H
#define A_OUT_DISPLAYSERVERCOMMAND_H


#include "../ICommand.h"

class DisplayServerCommand : public ICommand{

public:
    DisplayServerCommand(DefaultIO &io);

    ~DisplayServerCommand() override;

    void execute() override;

};
#endif //A_OUT_DISPLAYSERVERCOMMAND_H
