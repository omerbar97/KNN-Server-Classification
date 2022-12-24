



#include "Client.h"


Client::Client(int port_no, const char* ip_address){
    this->port_no = port_no;
    this->ip_address = "127.0.0.1";
    this->valid = true;
    if(!initSocket() ||  !initSin()) {
        this->valid = false;
    }




}
bool Client::initSocket() {
    //creating socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("error creating socket");
        return false;
    }
    this->socketNum = sock;
    return true;
}

//returnning false if faield.
bool Client::initSin() {
    memset(&this->sin, 0, sizeof(this->sin));
    this->sin.sin_family = AF_INET;
    this->sin.sin_addr.s_addr = inet_addr(this->ip_address);
    this->sin.sin_port = htons(port_no);
    if (connect(this->socketNum,(struct sockaddr*)&sin, sizeof(sin)) < 0){
        perror("error connecting to server");
        return false;
    }
    return true;
}



bool Client::SendData(char data_addr[], int data_len) {
    int sent_bytes = send(socketNum, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("error sending data");
        return false;
    }
    return true;
}

char* Client::readData() {
    int expected_data_len = sizeof(buffer);
    strcat(buffer, "");
    int read_bytes= recv(socketNum, buffer, expected_data_len,0);
    if (read_bytes == 0){
        // connection is closed
        perror("connection is closed");
        return nullptr;
    }
    else if (read_bytes<0) {
        perror("error reading data");
        return nullptr;
    }
    else {
        std::cout << buffer << "\n";
        return this->buffer;
    }
}

int Client::closeSock() {
    close(this->socketNum);
    return 0;
}


