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
        io.write("-1"); // error
        io.write(error.str()); // error message
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
    int port = START_PORT_THREAD + (this->p_Data->clientId % PORT_MODULO); // creating port for new server
    portString << port;
    // sending client port
    io.write(portString.str());

    // initializing server
    auto* downloadServer = new Server(port);
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
    io.write("1"); // able to continue.

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
        io.write("-1"); // error to client
        error.str("");
        error << "failed connecting the client-" << p_Data->clientId << " while trying to download files";
        perror(error.str().c_str());
        delete(downloadServer);
        return;
    }
    //succeeds connecting with thread client.
    io.write("1");

    auto* tempIo = new SocketIO(clientSocket);

    // sending arguments to thread function.
    auto* args = new DownloadFile();
    args->io = tempIo;
    args->server = downloadServer;
    args->filePath = nullptr;
    args->client = nullptr;
    args->p_Data = p_Data;

    std::thread t(newThreadDownload, (void*)args);
    // separating the thread from this function.
    t.detach();
}

void *DownloadServerCommand::newThreadDownload(void *args) {
    auto* temp = (DownloadFile*)args;
    std::stringstream message;
    size_t classifiedDataSize = temp->p_Data->classifiedResult->size();
    std::string check = temp->io->read(); // getting information on file
    if(check == "-1") {
        // error..
        std::cout << "client couldn't open the file to download\n";
    }
    else {
        for (int i = 0; i < classifiedDataSize; ++i) {
            message.str("");
            message << i + 1 << "\t" << temp->p_Data->classifiedResult->at(i);
            temp->io->write(message.str());
        }
        //symbol of end text
        temp->io->write("#");
    }

    // releasing memory
    delete(temp->server);
    delete(temp->io);
    delete(temp);
    return nullptr;
}
