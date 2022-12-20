//
// Created by shilo on 12/11/2022.
//
#include <iostream>
#include <string>
#include "calculate/Distance/Distance.h"
#include "calculate/ReadCSV.h"
#include "calculate/Algorithim/Knn.h"
#include "calculate/input.h"
using namespace std;


int main(int argc, char *args[]) {
    if(argc != 4) {
        input::error();
        return 0;
    }
    // initializing variables.
    // getting data from args:
    std::string result;
    std::string fileName = args[2];
    std::string filePath = "../resources/datasets/" + fileName;
    std::string vInput;
    Distance* distanceAlgo = nullptr;
    int k;
    // getting data from args
    try {
        // parsing string to int:
        k = std::stoi(args[1]);
    }
    catch (const std::invalid_argument &e) {
        input::error();
        return 0;
    }

    distanceAlgo = input::getDistance(args[3]);
    if(distanceAlgo == nullptr) {
        input::error();
        return 0;
    }
    // getting user input vector
    while(true) {
        getline(cin, vInput);
        std::vector<double> v;
        // checking user input:
        if(input::checkVectorInput(vInput)) {
            // converting the vector into string vector.
            std::vector<std::string> sVector = input::splitString(vInput);
            // converting the vector into vector of doubles.
            v = input::convertStrVecToDoubleVec(sVector);
            // read the data from the file
            ReadCSV readCsv(filePath);
            Knn knn(v, readCsv.getData(), distanceAlgo, k);

            if(knn.getClassified().empty()) {
                result = "Couldn't calculate the result, the vector that was inserted was not in the same size"
                         " like every other vector in: \n" + fileName + " Or in the file there is a vector not "
                                                                      "in the same size.";
                std::cout << result  << "\n";
                break;
            }
            else {
                result = knn.getClassified();
                std::cout << result  << "\n";
                continue;
            }
        }
        else{
            result = "Couldn't calculate the result, the vector that was inserted was not in the same size"
                     " like every other vector in: \n" + fileName + " Or in the file there is a vector not "
                                                                  "in the same size.";
            std::cout << result  << "\n";
            break;
        }
    }
    // deleting the distance algorithim at the end of use.
    delete distanceAlgo;
    distanceAlgo = nullptr; // after deletion
    return 0;
}
