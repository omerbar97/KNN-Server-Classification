//
// Created by oem on 1/14/23.
//

#include "DisplayClientCommand.h"

DisplayClientCommand::DisplayClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "4. display result\n";

}

DisplayClientCommand::~DisplayClientCommand() {
    std::string receiveData;

    //send "3" to server for option-2(algorithm setting).
    io.write("4");

    //read each line and print, when done the server will send "#"
    receiveData = io.read();
    while (receiveData != "#"){
        printf("%s\n", receiveData.c_str());
        receiveData = io.read();
    }

}

void DisplayClientCommand::execute() {


}
