//
// Created by omerb on 02/12/2022.
//
#include "Knn.h"
#ifndef RUNNABLE_SELECT_H
#define RUNNABLE_SELECT_H


class Select {
private:
    std::vector<DistanceVec>& distanceVector;
    int k;

    void swap(DistanceVec &v1, DistanceVec &v2);
    int initPartition(int lowIndex, int highIndex);
    void calculatePartition(int lowIndex, int highIndex, int kElement);

public:

    Select(std::vector<DistanceVec> &dVector, int kElement);
    void calculate();
};


#endif //RUNNABLE_SELECT_H
