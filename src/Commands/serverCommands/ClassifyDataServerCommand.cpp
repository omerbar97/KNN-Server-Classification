//
// Created by oem on 1/14/23.
//

#include "ClassifyDataServerCommand.h"

#include <utility>


ClassifyDataServerCommand::ClassifyDataServerCommand(DefaultIO &io) : ICommand(io) {
    this->description = "3. classify data\n";
}

void ClassifyDataServerCommand::execute() {
    std::string sendData;
    //if we there data isn't in map
    auto iterator = this->serverData.find(this->clientId);
//    if(iterator == (this->serverData).end()) {
//        io.write("please upload data\n");
//        return;
//    }
    //we found in data;
    if(iterator->second.testData.empty() || iterator->second.trainData.empty()) {
        io.write("please upload data\n");
        return;
    }
    clientData lineData = iterator->second;

    //we will classified the data



}
ClassifyDataServerCommand::~ClassifyDataServerCommand() noexcept {

}




