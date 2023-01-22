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
    bool newLine = true;

public:

    /**
     * constructor for fileIO class, create an file input and output class to handle the write and read from file
     * given fstream (file) and boolean value for default new line.
     * @param stream - file (fstream)
     * @param newLine - boolean
     */
    FileIO(std::fstream& stream, bool newLine = true);

    /**
     * default destructor
     */
    ~FileIO();

    /**
     * writing to fstream file, before calling this function make sure the file is open other wise, the function does
     * nothing (no write).
     * @param string - string to write.
     */
    void write(std::string string) override;

    /**
     * reading from file, make sure the file is open other wise empty string will return.
     * @return std::string
     */
    std::string read() override;

};


#endif //A_OUT_FILEIO_H
