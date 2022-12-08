//
// Created by omerb on 02/12/2022.
//

#include "Knn.h"

/**
 * Constructor getting all the information to calculate the Knn algorithim.
 * @param vInput - std::vector<double>
 * @param vectors - std::vector<VectorCSV>
 * @param distance - Distance
 * @param k - int
 */
Knn::Knn(std::vector<double> vInput,std::vector<VectorCSV> vectors, Distance* distance, int k)
                                : inputVector(vInput), multiVector(vectors){
    setK(k);
    setDistance(distance);
    calculate();
}

/**
 * getter for the distances result structure vector.
 * @return std::vector<DistanceVec>
 */
std::vector<DistanceVec> Knn::getDistances() {
    return resultVector;
}

/**
 * getting the class tag for the vectorInput
 * @return
 */
std::string Knn::getClassified() {
    return knnClassified;
}

/**
 * To change the distance algorithim for which the Knn works this method will change the logic algorithm.
 * @param distance - Distance
 */
void Knn::setDistance(Distance* d) {
    this->distance = d;
}

/**
 * to change the K parameter in the algorithm
 * @param k - int
 */
void Knn::setK(int newK) {
    this->k = newK;
}

/**
 * setting a new input vector.
 * @param inputVector - std::vector<double>
 */
void Knn::setVector(std::vector<double> iVector) {
    this->inputVector = iVector;
}

/**
 * calculating the K nearest neighbors and saving the result in the class results.
 * @param vectors - std::vector<VectorCSV>
 */
void Knn::calculate() {
    int minFlag = 1; // indicate if we need to return the min value of the distances. default = 1;
    std::vector<DistanceVec> temp;

    double result;
    // calculating all the distance between all the VectorCSV in multiVector with the inputVector.
    for(int i = 0; i < multiVector.size(); i++) {
        result = distance->operator()(multiVector[i].id, inputVector);
        if(result == -1) {
            // in case the vector was not in the same size cannot multiply.
            this->knnClassified.clear();
            return;
        }
        else {
            DistanceVec vec = {result, multiVector[i].name};
            temp.push_back(vec);
        }
    }

    // creating the select algorithm to calculate the K Elements size in the array.
    Select select(temp, k);
    select.calculate();

    // deleting all the vectors that is irrelevant. from the end to the K element.
    int sizeToDelete = temp.size();
    while(k < sizeToDelete) {
        temp.pop_back();
        sizeToDelete--;
    }

    // finding the minimum value of distance:
    DistanceVec vMin = temp[0];
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i].vData < vMin.vData) {
            vMin = temp[i];
        }
    }

    // counting how many times each tag was shown in the resultVector.
    std::map<std::string, int> counter;
    for(DistanceVec v : temp) {
        std::map<std::string, int>::iterator it = counter.find(v.className);
        if(it == counter.end()) {
            std::pair<std::string, int> s = {v.className, 0};
            counter.insert(s);
        }
        else {
            // increments the number of time the DistanceVec v is inside the Knn
            it->second += 1;
        }
    }

    // checking if the all tag's had appeared the same time.
    std::map<std::string, int>::iterator it = counter.find(vMin.className);
    for(std::pair<std::string, int> s : counter) {
        if(s.second != it->second) {
            minFlag = 0;
        }
    }

    // saving the result in the class variable.
    if(minFlag) {
        knnClassified = vMin.className;
    } else {
        // getting the max value from the map.
        std::map<std::string, int>::iterator itMax = counter.begin();
        for(std::map<std::string, int>::iterator iterator = counter.begin(); iterator != counter.end(); iterator++) {
            // setting new max
            if(itMax->second < iterator->second) {
                itMax = iterator;
            }
        }
        // saving the result in the class variable.
        knnClassified = itMax->first;
    }
}