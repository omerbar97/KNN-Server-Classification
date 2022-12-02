//
// Created by shilo on 02/12/2022.
//
#include <vector>
#include <string>
#ifndef MAIN_CPP_READCSV_H
#define MAIN_CPP_READCSV_H
#include "Algorithim/CSVStruct.h"
//build srruct
// read data, given path to file
//split data to Vector

class ReadCSV {

public:
    //return an array of Vector's (id and name).
    std::vector<VectorCSV> getData();

};

#endif //MAIN_CPP_READCSV_H
