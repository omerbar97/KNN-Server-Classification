//
// Created by omer on 1/13/23.
//

#include "UploadFilesCommand.h"

#include <utility>

UploadFilesCommand::UploadFilesCommand(DefaultIO &io) : ICommand(io) {
    this->description = "1. upload an unclassified csv data file\n";

}

void UploadFilesCommand::execute() const {
    // all the logics to get user locally file for trainer and second file for classified.
    // getting the user first trained file locally on computer this function will be called from the server side.
    io.write("Please upload your local train CSV file.\n");
    std::string trainedFile(io.read()); // reading from the client socket.
    if(!input::checkFilePath(trainedFile)) {
        // wrong input file.
        io.write("Wrong input file.\n");
        return;
    }

    // uploading to the server...


    io.write("Please upload your local test CSV file.\n");
    std::string testFile(io.read()); // reading from the client socket.
    if(!input::checkFilePath(testFile)) {
        // wrong input file.
        io.write("Wrong input file.\n");
        return;
    }

    // uploading to the server...
}

bool UploadFilesCommand::uploadFile(std::string file) {
    // return true if upload succeed.
    std::string line;
    int counter = 0;
    std::fstream fileStream(file, std::ios::in);
    if(fileStream.is_open()) {
        while (std::getline(fileStream, line)) {
            std::stringstream str(line);
            // getting the number until string appears
        }
    }
}

