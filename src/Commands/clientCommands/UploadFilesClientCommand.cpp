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
    std::string userInput, data, dataRec, check;

    // simbole for end file
    ICommand::io.write("1");

    //reading data from server to get instructions.
    dataRec = ICommand::io.read();
    std::cout << dataRec;

    //getting file path from user of train CSV file.
    std::getline(std::cin, userInput);

    // if the file is not valid.
    if (!input::checkFilePath(userInput)) {
        printf("invalid input!\n");
        ICommand::io.write("-1");
        return;
    }
    //else file train file is valid, read line by line and send the data
    ReadCSV::executeLines(this,userInput);

    // token for end file
    ICommand::io.write("#");

    check = io.read(); // if 1 the file valid -1 file not valid
    if(check == "-1") {
        // error
        std::cout << io.read();
        return;
    }

    //reading succes
    dataRec = io.read(); // upload succeed
    std::cout << dataRec;


    //reading data from server to get more instructions.
    dataRec = io.read();
    std::cout << dataRec; // upload the test file

    //getting file path from user of train CSV file.
    std::getline(std::cin, userInput);

    ///check if its really lodadded.

    // if the file is not valid.
    if (!input::checkFilePath(userInput)) {
        data = "invalid input!\n";
        ICommand::io.write(data);
        return;
    }
    //else file test file is valid, read line by line and send the data
    ReadCSV::executeLines(this,userInput);

    // simbole for end file
    ICommand::io.write("#");

    check = io.read(); // if 1 the file valid -1 file not valid
    if(check == "-1") {
        // error
        std::cout << io.read();
        return;
    }

    check = io.read();
    if(check == "-1") {
        //incompattible files
        std::cout << io.read();
        return;
    }

    dataRec = ICommand::io.read();
    std::cout << dataRec;

}
void UploadFilesClientCommand::setFileName(std::string name) {
    this->fileName = std::move(name);
}


