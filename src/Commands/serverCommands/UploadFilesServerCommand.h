//
// Created by omer on 1/13/23.
//

#ifndef A_OUT_UPLOADFILESSERVERCOMMAND_H
#define A_OUT_UPLOADFILESSERVERCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"

class UploadFilesServerCommand : public ICommand {
private:
    int clientId;
    bool uploadFile(std::string filePath);


public:

    UploadFilesServerCommand(DefaultIO &io, int clientId);

    ~UploadFilesServerCommand() override;

    void execute() override;

};


#endif //A_OUT_UPLOADFILESSERVERCOMMAND_H
