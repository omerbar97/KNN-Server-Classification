//
// Created by oem on 1/14/23.
//

#include "UploadFilesClientCommand.h"
#include "../../ReadCSV.h"
#include <utility>

UploadFilesClientCommand::UploadFilesClientCommand(DefaultIO &io) : ICommand(io){
    ICommand::description = "2";

}
void UploadFilesClientCommand::execute()  {
    std::string userInput, data, dataRec;

    //reading data from server to get instructions.
    dataRec = ICommand::io.read();
    std::cout << dataRec;

    //getting file path from user of train CSV file.
    std::getline(std::cin, userInput);

    // if the file is not valid.
    if (!input::checkFilePath(userInput)) {
        data = "invalid input!\n";
        ICommand::io.write(data);
        return;
    }
    //else file train file is valid, read line by line and send the data
    ReadCSV::executeLines(this,userInput);

    //reading data from server to get more instructions.
    dataRec = ICommand::io.read();
    std::cout << dataRec;

    //getting file path from user of train CSV file.
    std::getline(std::cin, userInput);

    // if the file is not valid.
    if (!input::checkFilePath(userInput)) {
        data = "invalid input!\n";
        ICommand::io.write(data);
        return;
    }

}
void UploadFilesClientCommand::setFileName(std::string name) {
    this->fileName = std::move(name);
}


