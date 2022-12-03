//
// Created by omerb on 02/12/2022.
//
#include <vector>
#include <string>
#include <iostream>
#include "../Distance/Distance.h"
#ifndef RUNNABLE_KNN_H
#define RUNNABLE_KNN_H
#include "../ReadCSV.h"
#include "CSVStruct.h"
#include "Select.h"
#include <map>


class Knn {

private:
    std::vector<VectorCSV> multiVector;
    std::vector<DistanceVec> resultVector;
    std::vector<double> inputVector;
    Distance* distance;
    int k;
    std::string knnClassified;

public:

    /**
    * Constructor getting all the information to calculate the Knn algorithim.
    * @param vInput - std::vector<double>
    * @param vectors - std::vector<Vector>
    * @param distance - Distance
    * @param k - int
    */
    Knn(std::vector<double> v1, std::vector<VectorCSV> vectors, Distance *distance, int k);
    /**
    * getter for the distances result structure vector.
    * @return std::vector<DistanceVec>
    */
    std::vector<DistanceVec> getDistances();

    void setVector(std::vector<double> inputVector);

    /**
    * To change the distance algorithim for which the Knn works this method will change the logic algorithm.
    * @param distance - Distance
    */
    void setDistance(Distance* distance);

    /**
    * to change the K parameter in the algorithm
    * @param k - int
    */
    void setK(int k);

    void calculate();

    /**
     * getting the classified result from the K-nn algorithm
     * @return
     */
    std::string getClassified();
};


#endif //RUNNABLE_KNN_H
