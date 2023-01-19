
#include "DownloadClientCommand.h"
#include <pthread.h>




DownloadClientCommand::DownloadClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "4. download result\n";
}
DownloadClientCommand::~DownloadClientCommand() {

}

void DownloadClientCommand::execute() {
    std::string receiveData, userInput;
    bool isValid = true;
    //send "5" to server for option-2(algorithm setting).
    io.write("5");

    //if ithere is problem with passsing the data
    if ((io.read()).compare("-1")) {
        std::cout << io.read(); // reading the error message.
        return;
    }
    std::cout << io.read();
    std::stringstream fileName;
    std::getline(std::cin, userInput);
    struct stat s;
    // checking if the path is legal
    if(stat(userInput.c_str(), &s) == 0) {
        if(s.st_mode & S_IFDIR)
        {
            //it's a directory
            fileName << userInput << "classifyResultsClientNumber-" << this->p_Data->clientId <<".txt";
        }
        else if(s.st_mode & S_IFREG)
        {
            //it's a file
            fileName << userInput;
        }
    }
    else {
        // error
        io.write("-1");
        return;
    }

    //there are valid input
    //create new file
    std::fstream file(fileName.str(), std::ios::out);
    FileIO fileResult(file, true);

    //loop over the file until got the sign #
    receiveData = io.read();
    while(!receiveData.compare("#")) {
        fileResult.write(receiveData);
        receiveData = io.read();
    }
}

void* DownloadClientCommand::executePath(void *arg) {
    execute();
}


