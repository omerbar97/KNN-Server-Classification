//
// Created by oem on 1/14/23.
//

#include "AlgorithemSettingClientCommand.h"


AlgorithemSettingClientCommand::AlgorithemSettingClientCommand(DefaultIO &io1) : ICommand(io1) {
    ICommand::description = "2. algorithm setting\n";
}


/**
 * function to implement algorithm setting, we get from the server a string with the format of
 * e.g "The current KNN parameters are: K = 5, distance metric = EUC"
 * and cluent change K,metric e.g "6 CHB", sending this data to server and change the setting.
 */
void AlgorithemSettingClientCommand::ICommand::execute()  {
    std::string receiveData, userInput;
    //get input from the user

    //send "2" to server for option-2(algorithm setting).
    io.write("2");

    //receive Data from server
    receiveData = io.read();

    //printing the format above that server sent.
    input::print(receiveData);

    //user send his asking.
    std::getline(std::cin, userInput);
    io.write(userInput);

    //receive Data from server and printing.
    receiveData = io.read();
    input::print(receiveData);
}