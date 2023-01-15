//
// Created by omer on 1/13/23.
//

#include "UploadFilesServerCommand.h"

#include <utility>

UploadFilesServerCommand::UploadFilesServerCommand(DefaultIO &io, int clientId) : ICommand(io) {
    this->description = "1. upload an unclassified csv data file\n";
    this->clientId = clientId;

}

void UploadFilesServerCommand::execute() {
    // all the logics to get user locally file for trainer and second file for classified.
    // getting the user first trained file locally on computer this function will be called from the server side.
    io.write("Please upload your local train CSV file.\n");
    // creating new folder for the client locally files.
    int status;
    std::string dirPath = &"mkdir -p ../../../temporaryFiles/client-" [this->clientId];
    status = system(dirPath.c_str());
    if(status == -1) {
        std::string error = &"failed creating temporary files for client number " [ this->clientId];
        perror(error.c_str());
        // sending error to socket.
        io.write("-1");
        return;
    }
    io.write("1"); // succeed creating the folder.
    // creating the trained file in the directory.
    std::stringstream train;
    train << "../../../temporaryFiles/client-" << this->clientId << "/train.txt";
    bool isSucceed = uploadFile(train.str());
    // sending to client Upload succeed.
    if(!isSucceed) {
        io.write("Failed Uploading\n");
        return;
    }
    io.write("Upload Succeed\n");

    // uploading test file.
    io.write("Please upload your local test CSV file.\n");
    std::stringstream test;
    test << "../../../temporaryFiles/client-" << this->clientId << "/test.txt";
    isSucceed = uploadFile(test.str());
    if(!isSucceed) {
        io.write("Failed Uploading\n");
        return;
    }
    io.write("Upload Succeed\n");
}

bool UploadFilesServerCommand::uploadFile(std::string filePath) {
    std::fstream trainedFile(filePath, std::ios::out);
    FileIO fileToWrite(trainedFile, false);
    if(trainedFile.is_open()) {
        while(true) {
            // uploading the file.
            std::string temp(io.read());
            if(strcmp(temp.c_str(), "#")) {
                // end file token
                break;
            }
            fileToWrite.write(temp);
        }
    }
    else {
        return false;
    }
    trainedFile.close();
    return true;
}


UploadFilesServerCommand::~UploadFilesServerCommand() {

}
