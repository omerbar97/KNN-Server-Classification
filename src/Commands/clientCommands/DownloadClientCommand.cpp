//
// Created by oem on 1/14/23.
//

#include "DownloadClientCommand.h"

DownloadClientCommand::DownloadClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "4. download result\n";
}
DownloadClientCommand::~DownloadClientCommand() {

}

void DownloadClientCommand::execute() {
    std::string receiveData;

    //send "5" to server for option-2(algorithm setting).
    io.write("5");

    //
}
