//
// Created by omer on 1/12/23.
//

#ifndef A_OUT_STANDARDIO_H
#define A_OUT_STANDARDIO_H
#include "DefaultIO.h"
#include <iostream>

class StandardIO :public DefaultIO {

private:
    std::string input;

public:

    StandardIO();

    void write(std::string string) override;

    std::string read() override;

    std::string getInput();

};


#endif //A_OUT_STANDARDIO_H
