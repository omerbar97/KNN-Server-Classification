//
// Created by oem on 1/14/23.
//
#include "ClassifyDataClientCommand.h"

ClassifyDataClientCommand::ClassifyDataClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "3. classify data\n";
}

/**
 * Client ask from server to classify the data that got sent then server respond with
 * "classify data complete" or please upload dara" respectively.
 */
void ClassifyDataClientCommand::ICommand::execute()  {
    std::string receiveData;

    //send "3" to server for option-2(algorithm setting).
    io.write("3");

    //receive Data from server
    receiveData = io.read();

    //printing the format above that server sent.
    input::print(receiveData);



}

ClassifyDataClientCommand::~ClassifyDataClientCommand() {


}

void ClassifyDataClientCommand::execute() {

}

