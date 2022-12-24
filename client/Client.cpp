



#include "Client.h"


Client::Client(int port_no, const char* ip_address) : port_no(port_no){
    this->port_no = port_no;
    this->ip_address = ip_address;
    initSin();
    initSocket();

}
bool Client::initSocket() {
    //creating socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("error creating socket");
        return false;
    }
    this->socketNum = sock;
    return false;
}

//returnning fale if faield.
bool Client::initSin() {
    struct sockaddr_in sin;
    memset(&sin, 0 , sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(this->ip_address);
    sin.sin_port = htons(port_no);
    if (connect(this->socketNum,(struct sockaddr*)&sin, sizeof(sin))<0){
        perror("error connecting to server");
        return false;
    }
    this->sin = sin;
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
    int read_bytes= recv(socketNum, buffer, expected_data_len,0);
    if (read_bytes ==0){
        // connection is closed
        perror("connection is closed");
        return nullptr;
    }
    else if (read_bytes<0) {
        perror("error reading data");
        return nullptr;
    }
    else {
        return this->buffer;
    }
}

int Client::closeSock() {
    close(this->socketNum);
    return 0;
}


