//
// Created by shilo on 02/12/2022.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "input.h"
#ifndef MAIN_CPP_READCSV_H
#define MAIN_CPP_READCSV_H
#include "Algorithim//CSVStruct.h"
#include "../src/Commands/ICommand.h"


class ReadCSV {

private:

    std::string fileName;
    std::vector<VectorCSV> data;
    std::ostream& stream;
    
    /**
    * This function move data from csv file to a vector of VectorCSV struct.
    * we assume in this function that each line in the data build with 5 word,
    * the first 4 words are numbers and the other onw is string.
    * In case that the function cannot open the file will printed in the screen
    * "could not open file"
    */
    void csvToData();

public:

    /**
     * getter for the data.
     * @return vector<VectorCSV>.
     */
    std::vector<VectorCSV> getData();
    /**
     * @param fileName string, path to csv file.
     */
    explicit ReadCSV(std::string fileName, std::ostream& stream);
    /**
     * print on the screen the data member.
    * we assume that the data contain vector of 4 numbers.
    */
    void printCvs();

    /**
     * This function get a command object and execute each line.
     * @param command
     */
    static void executeLines(ICommand* command, const std::string& fileName);
};

#endif //MAIN_CPP_READCSV_H
