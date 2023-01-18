//
// Created by omer on 1/18/23.
//

#ifndef A_OUT_DATASTRUCTS_H
#define A_OUT_DATASTRUCTS_H
#include <string>
#include "Algorithim/Knn.h"
#include "Algorithim/Knn.h"
#include <vector>

/**
 * DistanceVec struct
 * double vData - store the distance between some vector v1 to some inputVector.
 * std::string hold the vector classified name tag.
 */
struct DistanceVec{
    double vData;
    std::string className;
};

/**
 * VectorCSV struct
 * std::vector<double> hold the vector value.
 * std::string hold the classified name of the vector tag.
 */
struct VectorCSV {
    std::vector<double> id;
    std::string className;
};


struct clientData{
    std::vector<VectorCSV> trainData = {}; // empty vector
    std::vector<std::vector<double>> testData = {}; // empty vector
    std::vector<std::string> classifiedResult = {};
    int k = 5; // default value
    std::string metric = "EUC"; // default value;

};


struct ServerData{
    int clientSocket;
    int clientId;
    clientData data;
};

#endif //A_OUT_DATASTRUCTS_H

