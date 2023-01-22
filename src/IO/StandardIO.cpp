//
// Created by omer on 1/12/23.
//

#include "StandardIO.h"

void StandardIO::write(std::string string) {
    std::cout << string;
}

std::string StandardIO::read() {
    std::getline(std::cin, this->input);
    return getInput();
}

StandardIO::StandardIO() {

}

std::string StandardIO::getInput() {
    return this->input;
}
