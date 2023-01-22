//
// Created by oem on 1/14/23.
//

#include "DisplayClientCommand.h"

DisplayClientCommand::DisplayClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "4. display result\n";

}

DisplayClientCommand::~DisplayClientCommand() {


}

void DisplayClientCommand::execute() {
    std::string receiveData;
    std::stringstream message;

    //send "4" to server for option-4(display result).
    io.write("4");

    receiveData = io.read();
    //check if server have the asked data
    if (receiveData == "-1") {
        //data aren't available
        receiveData = io.read();
        std::cout << receiveData;
        return;
    }

    //otherwise data are available,
    //read each line and print, when done the server will send "#"
    receiveData = io.read();
    while (receiveData != "#"){
        std::cout << receiveData;
        receiveData = io.read();
    }

}
