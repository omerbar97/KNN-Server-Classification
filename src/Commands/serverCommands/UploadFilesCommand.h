//
// Created by omer on 1/13/23.
//

#ifndef A_OUT_UPLOADFILESCOMMAND_H
#define A_OUT_UPLOADFILESCOMMAND_H
#include "../ICommand.cpp"
#include <string>
#include "../../IO/DefaultIO.h"

class UploadFilesCommand : public ICommand {
private:

    bool uploadFile(std::string file);


public:

    UploadFilesCommand(DefaultIO &io);

    ~UploadFilesCommand();



    void execute() const override;

};


#endif //A_OUT_UPLOADFILESCOMMAND_H
