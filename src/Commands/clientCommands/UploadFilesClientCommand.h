//
// Created by oem on 1/14/23.
//

#ifndef A_OUT_UPLOADFILESCLIENTCOMMAND_H
#define A_OUT_UPLOADFILESCLIENTCOMMAND_H
#include "../ICommand.h"
#include <string>
#include "../../IO/DefaultIO.h"
#include "../../ReadCSV.h"


/**
 * This class is one of the command client can make.
 * which update to server the data.
 */
class UploadFilesClientCommand : public ICommand {
public:
    std::string fileName;
    /**
    * constructor that get the IO(connection between client to server).
    * @param io
    */
     UploadFilesClientCommand(DefaultIO &io);
     void execute() override;
     void setFileName(std::string fileName);
private:
};
#endif //A_OUT_UPLOADFILESCLIENTCOMMAND_H
