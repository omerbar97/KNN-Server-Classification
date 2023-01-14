//
// Created by omer on 1/13/23.
//

#ifndef A_OUT_UPLOADFILESSERVERCOMMAND_H
#define A_OUT_UPLOADFILESSERVERCOMMAND_H
#include "../ICommand.cpp"
#include <string>
#include "../../IO/DefaultIO.h"

class UploadFilesServerCommand : public ICommand {
private:

    bool uploadFile(std::string file);


public:

    UploadFilesServerCommand(DefaultIO &io);

    ~UploadFilesServerCommand();



    void execute() const override;

};


#endif //A_OUT_UPLOADFILESSERVERCOMMAND_H
