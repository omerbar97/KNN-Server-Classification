#include "Client.h"
#include <fstream>

bool isPort(const char * port) {
    try {
        std::atoi(port);
        return true;
    }
    catch(std::exception d) {
        return false;

    }
}
bool isIp(char * ip) {
    char * ptr;
    int counter = 0;
    ptr = strtok(ip,".");

    while (!ptr) {
        counter++;
        try {
            atoi(ptr);
            ptr = strtok(NULL,".");
        }catch (std::exception d) {
            return false;
        }
    }
    counter++;
    if(counter == 4) {
        return true;
    }
    return false;
}
bool userAskToClose(std::string str) {
    try {
        if (atoi(str.c_str()) == -1) {
            return true;
        }
    }catch (std::exception d) {
        return false;
    }
}
char* strToChrArray(std::string s) {
    char * data = new char [s.size()];
    for(int i = 0 ; i < s.size() ; i++) {
        data[i] = s[i];
    }
    return data;
}


int main(int argc, char *args[]) {
    int isOn = 1;
    std::string userInput;
    if(argc != 3 || !isPort(args[2]) || !isIp(args[1])) {
        std::cout<<"invalid input!" << std::endl;
    }
    //otherwise, the input is correct.
    const char* ip_address = args[1];
    int port_no = atoi(args[2]);

    //initializing  Client.
    Client client(port_no, ip_address);

    //looping and sending message from client to server until client send -1.
    while (isOn) {
        std::getline(std::cin, userInput);
        if(userAskToClose(userInput)) {
            //exit from the loop and close socket.
            client.closeSock();
            isOn = 0;
        }
        //otherwise, send the data to server.
        char * data = strToChrArray(userInput);
        client.SendData(data, userInput.size());
        client.readData();
    }
    return 0;
}