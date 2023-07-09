//
// Created by omerb on 02/12/2022.
//

#include "Select.h"

/**
 * constructor for class Select to src the K-Element in a std::Vector data structure.
 * @param dVector - std::vector<DistanceVec>
 * @param kElement - int
 */
Select::Select(std::vector<DistanceVec> &dVector, int kElement) : distanceVector(dVector){
    this->k = kElement;
}

/**
 * swap two structure of DistanceVec.
 * @param v1 - DistanceVec
 * @param v2 - DistanceVec
 */
void Select::swap(DistanceVec &v1, DistanceVec &v2) {
    DistanceVec temp = v1;
    v1 = v2;
    v2 = temp;
}

/**
 * doing the algorithm Partition
 * @param lowIndex - int
 * @param highIndex - int
 * @return int
 */
int Select::initPartition(int lowIndex, int highIndex) {
    int pivot, index, i;

    // setting low and high index.
    index = lowIndex;
    pivot = highIndex;

    // getting the pivot index.
    for(i=lowIndex; i < highIndex; i++) {
        if(distanceVector[i].vData < distanceVector[pivot].vData) {
            swap(distanceVector[i], distanceVector[index]);
            index++;
        }
    }
    // swapping value at high and at the index obtained.
    swap(distanceVector[pivot], distanceVector[index]);
    return index;
}

/**
 * the select algorithm.
 * @param lowIndex - int
 * @param highIndex - int
 */
void Select::calculatePartition(int lowIndex, int highIndex) {
    int pIndex;
    if(lowIndex < highIndex) {
        // partitioning array using last element as a pivot.
        // recursively implementing partitioning in the direction to place the pivot at (k - 1)th pivot.
        pIndex = initPartition(lowIndex, highIndex);
        if(pIndex == k - 1) {
            return;
        }
        else if(pIndex > k - 1)
            calculatePartition(lowIndex, pIndex - 1);
        else
            calculatePartition(pIndex + 1, highIndex);
    }
}

/**
 * public method to call to src.
 */
void Select::calculate() {
    calculatePartition(0, distanceVector.size() - 1);
}