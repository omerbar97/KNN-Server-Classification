//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_UPLOADFILESCLIENTCOMMAND_H
#define A_OUT_UPLOADFILESCLIENTCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"
#include "../../ReadCSV.h"

class UploadFilesClientCommand : public ICommand {
public:
    std::string fileName;
     UploadFilesClientCommand(DefaultIO &io);
     void execute() override;
     void setFileName(std::string fileName);
private:
};
#endif //A_OUT_UPLOADFILESCLIENTCOMMAND_H
