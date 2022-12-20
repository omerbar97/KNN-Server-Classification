//
// Created by omerb on 20/12/2022.
//
#include <iostream>
#include <string>
#include <cstring>
#include "Distance/Distance.h"
#include "Distance/Distance.h"
#include "Distance/Euclidean.h"
#include "Distance/Minkowski.h"
#include "Distance/Canberra.h"
#include "Distance/Chebyshev.h"
#include "Distance/Manhattan.h"
#ifndef A_OUT_INPUTS_H
#define A_OUT_INPUTS_H


/**
 * this namespace is all about the functions the handle all the inputs from the user ;
 * it's only purpose is to make the code more organized with all the functions, and to avoid duplicated
 * code from the server to the client.
 */
namespace input {

    std::vector<std::string> splitString(std::string str);
    bool isContainChar(std::vector<std::string> strVec);
    bool checkPropriety(std::string v1, std::string v2);
    bool checkVectorInput(std::string v);
    std::vector<double> convertStrVecToDoubleVec(std::vector<std::string> strVec);
    Distance* getDistance(std::string input);
    void print(std::string message = "", std::ostream& stream = std::cout);
    void error(std::ostream& stream = std::cout);
}


#endif //A_OUT_INPUTS_H
