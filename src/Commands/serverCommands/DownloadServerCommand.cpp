//
// Created by oem on 1/14/23.
//

#include "DownloadServerCommand.h"


DownloadServerCommand::DownloadServerCommand(DefaultIO &io) : ICommand(io){
    this->description = "5. download results\n";

}

DownloadServerCommand::~DownloadServerCommand() {

}

void DownloadServerCommand::execute(){
    std::stringstream message, check, error;
    //if not update files yet
    if (this->p_Data->testData == nullptr || this->p_Data->trainData == nullptr) {
        error << "Please upload data\n";
    }
    //if not classified data yet
    else if (this->p_Data->classifiedResult == nullptr) {
        error << "Please classify the data\n";
    }
    //if we have one of the above problem, send the message and return.
    if (error.rdbuf()->in_avail() != 0) {
        // metoraf
        io.write("-1");
        io.write(error.str());
        return;
    }
    std::stringstream temp;
    temp << this->p_Data->clientId;
    io.write(temp.str()); // able to download

    std::string localPath = "please specify locally file path to download result:\n";
    io.write(localPath);

    check << io.read();
    if(check.str() == "-1") {
        // error in locally path
        return;
    }
    // else opening new thread and downloading the file
    // creating new socket for the thread.

    std::stringstream portString;
    int port = 60000 + this->p_Data->clientId; // creating port for new server
    portString << port;
    // sending client port
    io.write(portString.str());

    // initializing server
    Server* downloadServer = new Server(port);
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int clientSocket;

    // init server
    if(!downloadServer->initServer()) {
        // send error
        delete(downloadServer);
        io.write("-1");
        return;
    }
    io.write("1");
    // listen to port
    if(!downloadServer->listenServer(1)) {
        delete(downloadServer);
        io.write("-1");
        return;
    }
    io.write("1");
    // sending client serverMainIp
    io.write(*p_Data->serverMainIp);

    // waiting for new client to connect the server
    clientSocket = accept(downloadServer->getSocketId(), (struct sockaddr *) &client_sin, &addr_len);
    if(clientSocket < 0) {
        io.write("-1");
        error.str("");
        error << "failed connecting the client-" << p_Data->clientId << " while trying to download files";
        perror(error.str().c_str());
        delete(downloadServer);
        return;
    }
    //succeeds connecting with thread client.
    io.write("1");

    SocketIO* tempIo = new SocketIO(clientSocket);

    // sending arguments to thread function.
    DownloadFile* args = (DownloadFile*)malloc(sizeof(DownloadFile));
    args->io = tempIo;
    args->server = downloadServer;
    args->filePath = nullptr;
    args->client = nullptr;
    args->p_Data = p_Data;
//    DownloadFile args = {tempIo, this->p_Data, nullptr, downloadServer};
    std::thread t(newThreadDownload, (void*)args);
    t.detach();
    //pthread_create(&tid, nullptr, newThreadDownload, (void*)&args);
    //otherwise send data to print by cline line by line
}

void *DownloadServerCommand::newThreadDownload(void *args) {
    auto* temp = (DownloadFile*)args;
    std::stringstream message;
    size_t classifiedDataSize = temp->p_Data->classifiedResult->size();
    for (int i = 0; i < classifiedDataSize; ++i) {
        message.str("");
        message << i + 1 << "\t" << temp->p_Data->classifiedResult->at(i);
        temp->io->write(message.str());
    }
    //symbol of end text
    temp->io->write("#");
    delete(temp->io);
    return nullptr;
}
