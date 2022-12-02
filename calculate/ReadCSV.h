//
// Created by shilo on 02/12/2022.
//
#include <vector>
#include <string>
#ifndef MAIN_CPP_READCSV_H
#define MAIN_CPP_READCSV_H

//build srruct
// read data, given path to file
//split data to Vector
struct Vector {
    std::vector<double> id;
    std::string name;
};

class ReadCSV {

public:
    //return an array of Vector's (id and name).
    std::vector<Vector> getData();

};

#endif //MAIN_CPP_READCSV_H
