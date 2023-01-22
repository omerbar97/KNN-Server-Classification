//
// Created by omer on 1/12/23.
//

#include "FileIO.h"


FileIO::FileIO(std::fstream &stream, bool newLine) : stream(stream) {
    this->newLine = newLine;
}

void FileIO::write(std::string string) {
    if(stream.is_open()) {
        if(newLine) {
            stream << string << "\n";
        }
        else {
            stream << string;
        }
    }
}

std::string FileIO::read() {
    if(stream.is_open()) {
        if(getline(stream, line)) {
            return line;
        }
    }
    // returning empty string if file is not open.
    return {};
}

FileIO::~FileIO() noexcept {
    stream.close();
}