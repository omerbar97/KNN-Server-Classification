#include "Client.h"
#include <iostream>
#include "../src/input.h"
#include "../src/Commands/clientCommands/AlgorithemSettingClientCommand.h"
#include "../src/Commands/clientCommands/ClassifyDataClientCommand.h"
#include "../src/Commands/clientCommands/DisplayClientCommand.h"
#include "../src/Commands/clientCommands/DownloadClientCommand.h"
#include "../src/Commands/clientCommands/UploadFilesClientCommand.h"
#include "../src/IO/SocketIO.h"
#include "../src/input.h"
#define IP_SIZE 15
#define BUFFER_SIZE 4096
#include "../src/IO/StandardIO.h"

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
    return false;
}
void* runOption5(void * arg) {
    static_cast<DownloadClientCommand*>(arg)->execute();
    return nullptr;
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
        << "Make sure the ip address is the same as the example and the port number is the same server port number.\n";
        exit(1);
    }
    //otherwise, the input is correct.
    const char* ip_address = args[1];
    int port_no = atoi(args[2]);

    //initializing  Client.
    Client client(port_no, ip_address);
    if(!client.getValid()) {
        input::print("failed to initializing the client.");
        printf("failed to initializing the client.\n");
//        input::print("failed to initializing the client.", client.getStream());
        exit(1);
    }
    //init SocketIO
    SocketIO socketIo(client.getsocketNum());
    //init list of the commands.
    DownloadClientCommand* pDownloadClientCommand = new DownloadClientCommand(socketIo);
    ICommand *option1 = new UploadFilesClientCommand(socketIo);
    ICommand *option2 = new AlgorithemSettingClientCommand(socketIo);
    ICommand *option3 = new ClassifyDataClientCommand(socketIo);
    ICommand *option4 = pDownloadClientCommand;
    ICommand *option5 = new DownloadClientCommand(socketIo);

//    std::vector<ICommand> commands{option1, option2, option3, option4, option5};
    std::vector<ICommand*> commandVec{option1, option1, option2, option3, option4, option5};

    //starting the connection with the server.
    //printing the options.
//    input::print(client.getBuffer());
//    //starting the connection with the server.
//    //printing the options.
//    printf("%s\n",client.readData());

    // input::print("Connected to the server successfully.\nSend the server the following to classified vectors\n"
    // "<vector> <distance algorithm> <integer k>", client.getStream());
    // looping and sending message from client to server until client send -1.
    while (true) {
        //receive Data from server and printing the optiond..
        printf("%s\n", client.readData());

        std::getline(std::cin, userInput);
        index = userAskToClose(userInput);
        if(index == -1) {
            standardIo.write("invalid input!\n");
            socketIo.write("-1"); // error
            continue;
        }
        if (index == 8) {
            //exit from the loop and close socket.
            client.closeSock();
            break;
        }
        if (index == 5) {
            pthread_t tid;
            void*(*func)(void *);
            pthread_create(&tid, NULL, runOption5,(void*)&pDownloadClientCommand);
            continue;
        }

        //otherwise execute the correct option.
        commandVec[index]->execute();

    }
    return 0;
}