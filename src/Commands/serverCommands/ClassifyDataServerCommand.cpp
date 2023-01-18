//
// Created by oem on 1/14/23.
//

#include "ClassifyDataServerCommand.h"

ClassifyDataServerCommand::ClassifyDataServerCommand(DefaultIO &io, int clientId) : ICommand(io),clientId(clientId), ServerCommands() {
    this->description = "3. classify data\n";
}

void ClassifyDataServerCommand::execute() {
    std::string sendData;
    //if we there data isn't in map
    auto iterator = this->data.find(this->clientId);
    if(iterator == (this->data).end()) {
        io.write("please upload data\n");
        return;
    }
    //we found in data;
    clientData lineData = iterator->second;

    //we will classified the data



}
ClassifyDataServerCommand::~ClassifyDataServerCommand() noexcept {

}
