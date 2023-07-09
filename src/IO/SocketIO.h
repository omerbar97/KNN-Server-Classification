//
// Created by omer on 1/12/23.
//

#ifndef A_OUT_SOCKETIO_H
#define A_OUT_SOCKETIO_H
#include "DefaultIO.h"
#include <string.h>
#include <sstream>

class SocketIO : public DefaultIO {

private:
    int socketNumber;
    bool valid;

public:

    /**
     * Constructor for creating the socket input/output, this class handle all the IO connection between 1 socket.
     * @param socket - int
     */
    SocketIO(int socket);

    /**
     * writing to the socket.
     * @param string - std::string
     */
    void write(std::string string) override;

    /**
     * reading from the socket. if couldn't read, return empty string.
     * @return std::string
     */
    std::string read() override;

    /**
     * returning if the current read/write is valid.
     * @return
     */
    bool isValid() const;

};


#endif //A_OUT_SOCKETIO_H
