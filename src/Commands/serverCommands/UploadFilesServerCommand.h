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

    bool uploadFile(std::string file);


public:

    UploadFilesServerCommand(DefaultIO &io);

    ~UploadFilesServerCommand() override;

    void execute() override;

};


#endif //A_OUT_UPLOADFILESSERVERCOMMAND_H
