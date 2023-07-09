#include "Client.h"
#include <iostream>
#include "../src/input.h"
#include "../src/Commands/clientCommands/AlgorithemSettingClientCommand.h"
#include "../src/Commands/clientCommands/ClassifyDataClientCommand.h"
#include "../src/Commands/clientCommands/DisplayClientCommand.h"
#include "../src/Commands/clientCommands/DownloadClientCommand.h"
#include "../src/Commands/clientCommands/UploadFilesClientCommand.h"
#include "../src/input.h"
#define IP_SIZE 15
#define BUFFER_SIZE 4096
#define START_PORT 1024
#define END_PORT 59999
#include "../src/IO/StandardIO.h"

/**
 * This function check if char* is in a correct pattern of ip.
 * @param port  const char *.
 * @return bool.
 */
bool isPort(const char *port) {
    int x;
    x = atoi(port);
    if(x >= START_PORT && x < END_PORT) {
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
    if(ptr == nullptr) {
        return false;
    }
    memcpy(ptr, ip, IP_SIZE);
    int counter = 0;
    //take the  part until the first point.
    ptr = strtok(ptr,".");
    while (ptr != nullptr) {
        counter++;
        //atoi function return 0 for any fail, so we check also that the string is not the number 0.
        if(atoi(ptr) == 0 && *ptr != '0') {
            free(ptr);
            return false;
        }
        atoi(ptr);
        ptr = strtok(nullptr,".");
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
int userAskToClose(std::string str) {
    try {
        int x = atoi(str.c_str());
        //if user input is one of the options
        if ((x <= 5 && x >=1 ) || x == 8) {
            return x;
        //user input is invalid.
        } else {
            return -1;
        }
    }
    catch (std::exception d) {
        return false;
    }
}

int main(int argc, char *args[]) {
    std::string userInput;
    StandardIO standardIo;
    int index;
    if(argc != 3 || !isPort(args[2]) || !isIp(args[1])) {
        // invalid argument input.
        std::cout <<"Invalid argument input, please make sure you execute the program as follow:\n"
        << "./client.out <ip_address> <server_port>\n"
        << "for example: ./client.out 127.0.0.1 12345\n"
        << "Make sure the ip address is the same as the example and the port number is the same server port number.\n"
           "valid port number more or equal to 1024 and less then 60000\n";
        // exit program need to restart.
        exit(1);
    }
    //otherwise, the input is correct.
    const char* ip_address = args[1];
    int port_no = atoi(args[2]);

    //initializing  Client.
    auto* client = new Client(port_no, ip_address);
    if(!client->getValid()) {
        standardIo.write("failed to initializing the client.\n");
        // deleting client and exiting program.
        delete(client);
        exit(1);
    }
    //init SocketIO
    SocketIO socketIo(client->getsocketNum());
    //init list of the commands.
    ICommand *option1 = new UploadFilesClientCommand(socketIo);
    ICommand *option2 = new AlgorithemSettingClientCommand(socketIo);
    ICommand *option3 = new ClassifyDataClientCommand(socketIo);
    ICommand *option4 = new DisplayClientCommand(socketIo);
    ICommand *option5 = new DownloadClientCommand(socketIo);

    std::vector<ICommand*> commandVec{option1, option2, option3, option4, option5};

    std::string message;
    std::stringstream send;
    while (true) {
        message = socketIo.read();
        std::cout << message << std::endl;
        //receive Data from server and printing the optiond..
        std::getline(std::cin, userInput);
        index = userAskToClose(userInput);
        if(index == -1) {
            standardIo.write("invalid input!\n");
            socketIo.write("-1"); // error
            continue;
        }
        if (index == 8) {
            //exit from the loop and close socket.
            socketIo.write("8");
            break;
        }
        //otherwise execute the correct option.
        commandVec[index - 1]->execute();
    }
    // freeing memory
    for(ICommand* i : commandVec) {
        delete(i);
    }
    client->closeSock();
    delete(client);
    return 0;
}