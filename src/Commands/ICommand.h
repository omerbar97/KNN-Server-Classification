//
// Created by omer on 1/12/23.
//

#ifndef A_OUT_ICOMMAND_H
#define A_OUT_ICOMMAND_H
#include "../input.h"
#include "../DataStructs.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "../IO/DefaultIO.h"
#include <utility>
#include "../IO/DefaultIO.h"
#include "../IO/FileIO.h"
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>

/**
 * this class are abstract class for action that client and server need to know to do(execute function).
 */
class ICommand {
public:
    std::string description;
    DefaultIO& io;
    clientData * p_Data;
    pthread_t tid;
/**
 * Constructor that get IO (what kind of connection we want the client or the server doing,
 * its can be from socket to socket or for standardIo)
 * @param io DefaultIO.
 */
    ICommand(DefaultIO &io) : io(io) {

    }
    virtual ~ICommand() {

    }
    /**
     * Abstract function that all the sons need to overwrite, this function to some functionality dependent on the class.
     */
    virtual void execute() = 0;
};

#endif //A_OUT_ICOMMAND_H
