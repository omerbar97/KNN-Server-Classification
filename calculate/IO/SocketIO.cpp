//
// Created by omer on 1/12/23.
//

#include "SocketIO.h"

SocketIO::SocketIO(int socket) {
    this->socketNumber = socket;
}

void SocketIO::write(std::string string){
    int message;
    char bufferToSend[BUFFER];
    strcpy(bufferToSend, string.c_str());
    message = send(this->socketNumber, bufferToSend, BUFFER, 0);
    if(message < 0) {
        perror("failed sending data");
        this->valid = false;
    }
    else {
        this->valid = true;
    }
}

std::string SocketIO::read(){
    int message;
    char bufferToSend[BUFFER];
    message = recv(this->socketNumber, bufferToSend, BUFFER, 0);
    if(message < 0) {
        perror("failed receiving data");
        this->valid = false;
    }
    else {
        this->valid = true;
    }
}

bool SocketIO::isValid() {
    return this->valid;
}
