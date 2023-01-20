
#include "DownloadClientCommand.h"
#include <pthread.h>




DownloadClientCommand::DownloadClientCommand(DefaultIO &io) : ICommand(io) {
    ICommand::description = "4. download result\n";
}
DownloadClientCommand::~DownloadClientCommand() {

}

void DownloadClientCommand::execute() {
    std::string receiveData, userInput, serverIp, temp;
    //send "5" to server for option-2(algorithm setting).
    io.write("5");

    //if ithere is problem with passsing the data
    std::string clientId = io.read();
    if (strcmp(clientId.c_str(), "-1") == 0) {
        std::cout << io.read(); // reading the error message.
        return;
    }
    std::cout << io.read(); // please upload file
    std::stringstream fileName;
    std::getline(std::cin, userInput);
    struct stat s;
    // checking if the path is legal
    if(stat(userInput.c_str(), &s) == 0) {
        if(s.st_mode & S_IFDIR)
        {
            //it's a directory
            fileName << userInput << "/classifyResultsClientNumber-" << clientId << ".txt";
        }
        else if(s.st_mode & S_IFREG)
        {
            //it's a file
            fileName << userInput;
        }
        else {
            io.write("-1");
            return;
        }
    }
    else {
        // error
        io.write("-1");
        return;
    }
    io.write("1"); // able to download.
    // opening new thread to download the file.
    int check;
    int port = atoi(io.read().c_str());

    temp = io.read();
    if(temp == "-1") { // initSocket from server failed
        // error

        return;
    }
    temp = io.read();
    if(temp == "-1") { // listen server socket failed
        // error

        return;
    }
    serverIp = io.read();
    Client *downloadClient = new Client(port, serverIp.c_str());
    temp = io.read();
    if(temp == "-1") {
        // error
        std::cout << "failed downloading file: thread connection exception" << std::endl;
        delete(downloadClient);
        io.read(); // reading "-1"
        return;
    }

    SocketIO* tempIo = new SocketIO(downloadClient->getsocketNum());
    auto args = (DownloadFile*)malloc(sizeof(DownloadFile));
    args->io = tempIo;
    args->filePath = new std::string(fileName.str());
    args->client = downloadClient;
    args->p_Data = nullptr;
    args->server = nullptr;
    std::thread t(newThreadDownloadClient, (void*)args);
    t.detach();
    //pthread_create(&tid, nullptr, newThreadDownload, (void*)&args);
}


void *DownloadClientCommand::newThreadDownloadClient(void *args) {
    //create new file
    std::cout << "in client new thread";
    std::string receiveData;
    DownloadFile* temp = (DownloadFile*)args;
    std::fstream file(*temp->filePath, std::ios::out);
    FileIO fileResult(file, true);
    //loop over the file until got the sign #
    receiveData = temp->io->read();
    if(file.is_open()) {
        while(receiveData != "#") {
            fileResult.write(receiveData);
            receiveData = temp->io->read();
        }
    }
    file.close();

    // deleting resources
    delete(temp->io);
    delete(temp->client);
    delete(temp->filePath);
    return nullptr;
}


