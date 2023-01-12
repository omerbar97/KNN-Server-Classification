//
// Created by omer on 1/12/23.
//

#ifndef A_OUT_SOCKETIO_H
#define A_OUT_SOCKETIO_H
#include "DefaultIO.h"
#include <string.h>

class SocketIO : public DefaultIO {

private:
    int socketNumber;
    bool valid;

public:

    SocketIO(int socket);
    void write(std::string string) override;
    std::string read() override;
    bool isValid();

};


#endif //A_OUT_SOCKETIO_H
