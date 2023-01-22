//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DISPLAYCLIENTCOMMAND_H
#define A_OUT_DISPLAYCLIENTCOMMAND_H
#include "../ICommand.h"
#include "../../IO/DefaultIO.h"
/**
 * This class is one of the command client can make.
 * which display the result of the classify data.
 */
class DisplayClientCommand : public ICommand {
public:
    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
    DisplayClientCommand(DefaultIO &io);
    ~DisplayClientCommand() override;
    void execute() override;


};
#endif //A_OUT_DISPLAYCLIENTCOMMAND_H
