//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DISPLAYCLIENTCOMMAND_H
#define A_OUT_DISPLAYCLIENTCOMMAND_H
#include "../ICommand.h"
#include "../../IO/DefaultIO.h"

class DisplayClientCommand : public ICommand {
public:
    DisplayClientCommand(DefaultIO &io);
    ~DisplayClientCommand() override;
    void execute() override;


};
#endif //A_OUT_DISPLAYCLIENTCOMMAND_H
