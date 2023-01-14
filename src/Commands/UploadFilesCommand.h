//
// Created by omer on 1/13/23.
//

#ifndef A_OUT_UPLOADFILESCOMMAND_H
#define A_OUT_UPLOADFILESCOMMAND_H
#include "ICommand.h"
#include <string>
#include "../IO/DefaultIO.h"

class UploadFilesCommand :  private ICommand {
private:

    bool uploadFile(std::string file);


public:

    UploadFilesCommand(std::string description, DefaultIO &io);

    ~UploadFilesCommand();



    void execute() const override;

};


#endif //A_OUT_UPLOADFILESCOMMAND_H
