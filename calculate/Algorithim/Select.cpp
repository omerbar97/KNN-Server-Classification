//
// Created by omerb on 02/12/2022.
//

#include "Select.h"

Select::Select(std::vector<DistanceVec> &dVector, int kElement) : distanceVector(dVector){
    this->k = kElement;
}

void Select::swap(DistanceVec &v1, DistanceVec &v2) {
    DistanceVec temp = v1;
    v1 = v2;
    v2 = temp;
}

int Select::initPartition(int lowIndex, int highIndex) {
    int pivot, index, i;

    // setting low and high index.
    index = lowIndex;
    pivot = highIndex;

    // getting the pivot index.
    for(i=lowIndex; i < highIndex; i++)
    {
        if(distanceVector[i].vData < distanceVector[pivot].vData)
        {
            swap(distanceVector[i], distanceVector[index]);
            index++;
        }
    }
    // swapping value at high and at the index obtained.
    swap(distanceVector[pivot], distanceVector[index]);
    return index;
}

void Select::calculatePartition(int lowIndex, int highIndex, int kElement) {
    int pIndex;
    if(lowIndex < highIndex)
    {
        // partitioning array using last element as a pivot.
        // recursively implementing partitioning in the direction to place the pivot at (k - 1)th pivot.
        pIndex = initPartition(lowIndex, highIndex);
        if(pIndex == k - 1) {
            return;
        }
        else if(pIndex > k - 1)
            calculatePartition(lowIndex, pIndex - 1, k);
        else
            calculatePartition(pIndex + 1, highIndex, k);
    }
}

void Select::calculate() {
    calculatePartition(0, this->distanceVector.size() - 1, this->k);
}