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
void AlgorithemSettingClientCommand::execute()  {
    std::string receiveData, userInput;
    //get input from the user

    //send "2" to server for option-2(algorithm setting).
    io.write("2");

    //receive Data from server
    receiveData = io.read();

    //printing the format above that server sent.
    std::cout << receiveData << std::endl;

    //user send his asking with format "6 CHB".
    std::getline(std::cin, userInput);
    if(userInput == "") {
        io.write("#"); // no need to replace
        return;
    }
    io.write("$"); // need to replace
    io.write(userInput);

    //check if data are not valid
    receiveData = io.read();
    std::cout << receiveData;

}
AlgorithemSettingClientCommand::~AlgorithemSettingClientCommand() {

}