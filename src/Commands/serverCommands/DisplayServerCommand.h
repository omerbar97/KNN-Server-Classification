//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_DISPLAYSERVERCOMMAND_H
#define A_OUT_DISPLAYSERVERCOMMAND_H


#include "../ICommand.h"
/**
 * This class is one of the command client can make.
 * which display the result of the classify data.
 */
class DisplayServerCommand : public ICommand{

public:
    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
    DisplayServerCommand(DefaultIO &io);

    ~DisplayServerCommand() override;

    void execute() override;

};
#endif //A_OUT_DISPLAYSERVERCOMMAND_H
