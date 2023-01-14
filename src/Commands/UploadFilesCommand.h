//
// Created by omer on 1/13/23.
//

#ifndef A_OUT_UPLOADFILESCOMMAND_H
#define A_OUT_UPLOADFILESCOMMAND_H
#include "ICommand.h"
#include <string>
#include "../IO/DefaultIO.h"
#include "../../server/Server.h"

class UploadFilesCommand : public ICommand {
private:
    Server& server;
    bool uploadFile(std::string file);


public:

    UploadFilesCommand(std::string description, DefaultIO &io, Server &server);

    ~UploadFilesCommand() override;



    void execute() const override;

};


#endif //A_OUT_UPLOADFILESCOMMAND_H
