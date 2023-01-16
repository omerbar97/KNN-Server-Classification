
#include "DownloadClientCommand.h"
#include <pthread.h>




DownloadClientCommand::DownloadClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "4. download result\n";
}
DownloadClientCommand::~DownloadClientCommand() {

}

void DownloadClientCommand::execute() {
    std::string receiveData;

    //send "5" to server for option-2(algorithm setting).
    io.write("5");

    //if ithere is problem with passsing the data
    if ((io.read()).compare("-1")) {
        std::cout<<"invalid input!"<<std::endl;
        return;
    }

    //there are valid input

    //create new file
    std::ofstream file("downloadResult.txt");

    //loop over the file until got the sign #
    receiveData = io.read();
    while(!receiveData.compare("#")) {
        file << receiveData << std::endl;
        receiveData = io.read();

    }
}

