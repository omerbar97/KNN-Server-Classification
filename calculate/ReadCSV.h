//
// Created by shilo on 02/12/2022.
//
#include <vector>
#include <string>
#ifndef MAIN_CPP_READCSV_H
#define MAIN_CPP_READCSV_H
#include "Algorithim//CSVStruct.h"


class ReadCSV {

private:

    std::string fileName;
    std::vector<VectorCSV> data;
    
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
    explicit ReadCSV(std::string fileName);
    /**
     * print on the screen the data member.
    * we assume that the data contain vector of 4 numbers.
    */
    void printCvs();
};

#endif //MAIN_CPP_READCSV_H
