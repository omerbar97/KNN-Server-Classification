//
// Created by omer on 1/12/23.
//

#ifndef A_OUT_FILEIO_H
#define A_OUT_FILEIO_H
#include "DefaultIO.h"
#include <fstream>


class FileIO : public DefaultIO {
private:
    std::string line;
    std::fstream& stream;
    std::string filePath;
    bool newLine = true;

public:
    FileIO(std::string filePath, std::fstream& stream, bool newLine = true);
    ~FileIO();

    void write(std::string string) override;
    std::string read() override;




};


#endif //A_OUT_FILEIO_H
