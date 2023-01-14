//
// Created by omer on 1/12/23.
//

#include "FileIO.h"

#include <utility>

FileIO::FileIO(std::string filePath, std::fstream &stream, bool newLine) : stream(stream), filePath(std::move(filePath)){
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
    return {};
}

FileIO::~FileIO() noexcept {
    stream.close();
}