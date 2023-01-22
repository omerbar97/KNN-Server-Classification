
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

    //if there is problem with passing the data
    std::string clientId = io.read();
    if (clientId == "-1") {
        std::cout << io.read(); // reading the error message.
        return;
    }

    std::cout << io.read(); // please upload file
    std::stringstream fileName;
    std::getline(std::cin, userInput);
    struct stat fileStats;
    // checking if the path is legal
    if(stat(userInput.c_str(), &fileStats) == 0) {
        if(fileStats.st_mode & S_IFDIR)
        {
            //it's a directory, adding default file.
            fileName << userInput << "/classifyResultsClientNumber-" << clientId << ".txt";
        }
        else if(fileStats.st_mode & S_IFREG)
        {
            //it's a file.
            fileName << userInput;
        }
        else {
            // else error
            io.write("-1");
            return;
        }
    }
    else {
        // the file does not exist, creating the file
        fileName << userInput;
    }
    io.write("1"); // able to download.

    int port = atoi(io.read().c_str());

    temp = io.read();
    if(temp == "-1") { // initSocket from server failed
        // error
        std::cout << "failed initizling new socket to download the file in a new thread.\n";
        return;
    }
    temp = io.read();
    if(temp == "-1") { // listen server socket failed
        // error
        std::cout << "the listen socket in the new server failed.\n";
        return;
    }

    // reading server ip for new client, default is: 127.0.0.1
    serverIp = io.read();
    auto *downloadClient = new Client(port, serverIp.c_str());

    temp = io.read();
    if(temp == "-1") {
        // error
        std::cout << "failed downloading file: thread connection exception" << std::endl;
        delete(downloadClient);
        io.read(); // reading "-1"
        return;
    }

    auto* tempIo = new SocketIO(downloadClient->getsocketNum());
    auto args = new DownloadFile();

    // initializing data for new thread
    args->io = tempIo;
    args->filePath = new std::string(fileName.str());
    args->client = downloadClient;
    args->p_Data = nullptr;
    args->server = nullptr;

    // creating new thread.
    std::thread t(newThreadDownloadClient, (void*)args);
    // setting thread detached
    t.detach();
}


void *DownloadClientCommand::newThreadDownloadClient(void *args) {
    //create new file
    std::string receiveData;
    auto* temp = (DownloadFile*)args;
    std::fstream file(*temp->filePath, std::ios::out);
    FileIO fileResult(file, true);
    //loop over the file until got the sign #
    if(file.is_open()) {
        temp->io->write("1"); // file open
        receiveData = temp->io->read();
        while(receiveData != "#") {
            fileResult.write(receiveData);
            receiveData = temp->io->read();
        }
        file.close();
    }
    else {
        // file didn't open.
        temp->io->write("-1");
        std::cout << "failed downloading file, couldn't open file.\n";
    }

    // deleting resources
    delete(temp->io);
    delete(temp->client);
    delete(temp->filePath);
    delete(temp);
    return nullptr;
}


