//
// Created by omer on 1/12/23.
//

#include "StandardIO.h"

void StandardIO::write(std::string string) {
    std::cout << string;
}

std::string StandardIO::read() {
    char buffer[BUFFER];
    std::getline(std::cin, this->input);
}

StandardIO::StandardIO() {

}

std::string StandardIO::getInput() {
    return this->input;
}
