//
// Created by oem on 1/14/23.
//
#include "ClassifyDataClientCommand.h"

ClassifyDataClientCommand::ClassifyDataClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "3. classify data\n";
}



ClassifyDataClientCommand::~ClassifyDataClientCommand() {


}

/**
 * Client ask from server to classify the data that got sent then server respond with
 * "classify data complete" or please upload dara" respectively.
 */

void ClassifyDataClientCommand::execute() {
    std::string receiveData;

    //send "3" to server for option-3(classify data).
    io.write("3");

    if(strcmp(io.read().c_str(), "-1") == 0) {
        // error in setting:
        std::cout << io.read();
        return;
    }
    //receive Data from server
    receiveData = io.read();

    //printing the format above that server sent.
    std::cout << receiveData;
}


