
#include "DownloadClientCommand.h"
#include <pthread.h>




DownloadClientCommand::DownloadClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "4. download result\n";
}
DownloadClientCommand::~DownloadClientCommand() {

}

void DownloadClientCommand::execute() {
    std::string receiveData, userInput;
    //send "5" to server for option-2(algorithm setting).
    io.write("5");

    //if ithere is problem with passsing the data
    std::string clientId = io.read();
    if (strcmp(clientId.c_str(), "-1") == 0) {
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
            fileName << userInput << "classifyResultsClientNumber-" << clientId << ".txt";
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
    // opening new thread to download the file.
    io.write("1"); // able to download.
    pthread_t tid;
    DownloadFile args = {this->io, NULL, fileName.str()};
    pthread_create(&tid, NULL, newThreadDownload, (void*)&args);
}


void *DownloadClientCommand::newThreadDownload(void *args) {
    //create new file
    std::string receiveData;
    DownloadFile* temp = (DownloadFile*)args;
    std::fstream file(temp->filePath, std::ios::out);
    FileIO fileResult(file, true);

    //loop over the file until got the sign #
    receiveData = temp->io.read();
    if(file.is_open()) {
        while(!receiveData.compare("#")) {
            fileResult.write(receiveData);
            receiveData = temp->io.read();
        }
    }
    file.close();
}


