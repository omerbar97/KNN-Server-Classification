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

/**
 * This class is one of the command Server can make.
 * which update the client data in server.
 */
class UploadFilesServerCommand : public ICommand{
private:


public:
    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
    UploadFilesServerCommand(DefaultIO &io);

    ~UploadFilesServerCommand() override;

    void execute() override;

};


#endif //A_OUT_UPLOADFILESSERVERCOMMAND_H
