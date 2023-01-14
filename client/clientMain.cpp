#include "Client.h"
#include <fstream>
#include <iostream>
//#include "../calculate/input.h"
#include "../src/input.h"

#define IP_SIZE 15
#define BUFFER_SIZE 4096
//255.255.255.255
/**
 * This function check if char* is in a correct pattern of ip.
 * @param port  const char *.
 * @return bool.
 */
bool isPort(const char *port) {

    int x;
    x = atoi(port);
    if(x >= 1024 && x < 65536) {
        return true;
    }
    return false;
}
/**
 * This function get an const chat array and check if this array are match to the pattern of ip
 * which the pattern is x.y.z.q where x,y,z,q are numbers.
 * if thre tany unsuitability function will return false , otherwise return true.
 * @param ip const char *.
 * @return bool.
 */
bool isIp(const char *ip) {
    char *ptr = (char*)malloc(sizeof(ip)*IP_SIZE + 1);
    if(ptr == NULL) {
        return false;
    }
    memcpy(ptr, ip, IP_SIZE);
    int counter = 0;
    //take the  part until the first point.
    ptr = strtok(ptr,".");
    while (ptr != NULL) {
        counter++;
        //atoi function return 0 for any fail, so we check also that the string is not the number 0.
        if(atoi(ptr) == 0 && *ptr != '0') {
            free(ptr);
            return false;
        }
        atoi(ptr);
        ptr = strtok(NULL,".");
    }
    //if there are 4 parts correspond to the pattern.
    if(counter == 4) {
        free(ptr);
        return true;
    }
    free(ptr);
    return false;
}
/**
 * This function get a string and check if the string is -1 then return true, otherwise false.
 * @param str std::string str
 * @return bool.
 */
bool userAskToClose(std::string str) {
    try {
        if (atoi(str.c_str()) == -1) {
            return true;
        }
    }
    catch (std::exception d) {
        return false;
    }
    return false;
}



int main(int argc, char *args[]) {
    std::string userInput;
    if(argc != 3 || !isPort(args[2]) || !isIp(args[1])) {
        // invalid argument input.
        std::cout <<"Invalid argument input, please make sure you execute the program as follow:\n"
        << "./client.out <ip_address> <server_port>\n"
        << "for example: ./client.out 127.0.0.1 12345\n"
        << "Make sure the ip address is the same as the example and the port number is the same server port number.\n";
        exit(1);
    }
    //otherwise, the input is correct.
    const char* ip_address = args[1];
    int port_no = atoi(args[2]);

    //initializing  Client.
    Client client(port_no, ip_address, std::cout);
    if(!client.getValid()) {
        input::print("Failed to initializing the client.", client.getStream());
        exit(1);
    }
    input::print("Connected to the server successfully.\nSend the server the following to classified vectors\n"
                 "<vector> <distance algorithm> <integer k>", client.getStream());
    // looping and sending message from client to server until client send -1.
    while (true) {
        std::getline(std::cin, userInput);
        if(userAskToClose(userInput)) {
            //exit from the loop and close socket.
            client.closeSock();
            break;
        }
        //otherwise, send the data to server.
        char *data = input::strToChrArray(userInput);
        client.sendData(data, BUFFER_SIZE);
        client.readData();
        input::print(client.getBuffer(), client.getStream());
    }
    return 0;
}