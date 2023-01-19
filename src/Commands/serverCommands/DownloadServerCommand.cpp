//
// Created by oem on 1/14/23.
//

#include "DownloadServerCommand.h"


DownloadServerCommand::DownloadServerCommand(DefaultIO &io) : ICommand(io){
    this->description = "5. download results\n";

}

DownloadServerCommand::~DownloadServerCommand() {

}

void DownloadServerCommand::execute(){
    std::stringstream message, check;
    //if not update files yet
    if (this->p_Data->testData.empty() || this->p_Data->trainData.empty()) {
        message << "Please upload data\n";
    }
    //if not classified data yet
    else if (this->p_Data->classifiedResult.empty()) {
        message << "Please classify the data\n";
    }
    //if we have one of the above problem, send the message and return.
    if (message.rdbuf()->in_avail() != 0) {
        // metoraf
        io.write("-1");
        io.write(message.str());
        return;
    }

    std::string localPath = "please specify locally file path to download result:\n";
    io.write(localPath);

    check << io.read();
    if((check.str()).compare("-1")) {
        // error in locally path
        return;
    }
    // else opening new thread and downloading the file
    pthread_t tid;
    DownloadFile args = {this->io, this->p_Data};
    pthread_create(&tid, NULL, newThreadDownload, (void*)&args);
    //otherwise send data to print by cline line by line
}

void *DownloadServerCommand::newThreadDownload(void *args) {
    auto* temp = (DownloadFile*)args;
    std::stringstream message;
    size_t classifiedDataSize = temp->p_Data->classifiedResult.size();
    for (int i = 0; i < classifiedDataSize; ++i) {
        message.str("");
        message << i + 1 << temp->p_Data->classifiedResult[i] << std::endl;
        temp->io.write(message.str());
    }
    //symbol of end text
    temp->io.write("#");
    return NULL;
}
