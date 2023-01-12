//
// Created by omer on 1/12/23.
//

#ifndef A_OUT_DEFAULTIO_H
#define A_OUT_DEFAULTIO_H
#define BUFFER 4096
#include <sys/socket.h>
#include <string>

class DefaultIO {
public:

    /**
     * destructor for all the resources that the defaultIO class used.
     */
    virtual ~DefaultIO();

    /**
     * every class that inherits this abstract class need to implements the read method for reading the data from the stream.
     */
    virtual std::string read() = 0;

    /**
     * every class that inherits this abstract class need to implements the write method for writing the data to the stream.
     * @param string - string to write to the IO.
     */
    virtual void write(std::string string) = 0;
};


#endif //A_OUT_DEFAULTIO_H
