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

    // simbole for end file
    ICommand::io.write("1");

    //reading data from server to get instructions.(train)
    dataRec = ICommand::io.read();
    std::cout << dataRec;

    //getting file path from user of train CSV file.
    std::getline(std::cin, userInput);

    // if the file is not valid.
    if (!input::checkFilePath(userInput)) {
        std::cout << "invalid input!"<<std::endl;
        ICommand::io.write("-1");
        return;
    }
    //else file train file is valid, read line by line and send the data
    ReadCSV::executeLines(this,userInput);



    // simbole for end file
    ICommand::io.write("#");

    if(atoi(io.read().c_str()) == -1) {
        std::cout << "invalid input!"<<std::endl;
        return;
    }
    //reading data from server to get more instructions.
    dataRec = ICommand::io.read();
    std::cout << dataRec;

    //getting file path from user of train CSV file.
    std::getline(std::cin, userInput);


    // if the file is not valid.
    if (!input::checkFilePath(userInput)) {
        std::cout << "invalid input!"<<std::endl;
        ICommand::io.write("-1");
        return;
    }
    //else file test file is valid, read line by line and send the data
    ReadCSV::executeLines(this,userInput);

    // simbole for end file
    ICommand::io.write("#");

    if(atoi(io.read().c_str()) == -1) {
        std::cout << "invalid input!"<<std::endl;
    }
}
void UploadFilesClientCommand::setFileName(std::string name) {
    this->fileName = std::move(name);
}


