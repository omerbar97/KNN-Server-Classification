//
// Created by omerb on 02/12/2022.
//
#ifndef RUNNABLE_SELECT_H
#define RUNNABLE_SELECT_H
#include "../DataStructs.h"

class Select {

private:
    /**
     * private variables.
     */
    std::vector<DistanceVec>& distanceVector;
    int k;

    /**
     * private Functions:
     */
    void swap(DistanceVec &v1, DistanceVec &v2);

    int initPartition(int lowIndex, int highIndex);

    void calculatePartition(int lowIndex, int highIndex);


public:

    Select(std::vector<DistanceVec> &dVector, int kElement);

    void calculate();
};


#endif //RUNNABLE_SELECT_H
