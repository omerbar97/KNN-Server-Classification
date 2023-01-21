//
// Created by omer on 1/13/23.
//

#ifndef A_OUT_UPLOADFILESSERVERCOMMAND_H
#define A_OUT_UPLOADFILESSERVERCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"
#include <sstream>
#include <string>
#include <utility>
#include <iostream>
#include <map>


class UploadFilesServerCommand : public ICommand{
private:


public:

    UploadFilesServerCommand(DefaultIO &io);

    ~UploadFilesServerCommand() override;

    void execute() override;

};


#endif //A_OUT_UPLOADFILESSERVERCOMMAND_H
