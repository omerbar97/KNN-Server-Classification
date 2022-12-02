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
Knn::Knn(std::vector<double> vInput,std::vector<VectorCSV> vectors, Distance* distance, int k) : inputVector(vInput){
    setK(k);
    setDistance(distance);
    calculate(vectors);
}

/**
 * getter for the distances result structure vector.
 * @return std::vector<DistanceVec>
 */
std::vector<DistanceVec> Knn::getDistances() {
    return resultVector;
}

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
void Knn::calculate(std::vector<VectorCSV> vectors) {
    //std::vector<DistanceVec> temp;
    //temp.push_back(DistanceVec())
    double res;
    // calculating all the distance between all the vectors in vectors and to the inputVector.
    for(int i = 0; i < vectors.size(); i++) {
        res = distance->operator()(vectors[i].id, inputVector);
        DistanceVec vec = {res, vectors[i].name};
        resultVector.push_back(vec);
    }
    for (DistanceVec v : resultVector) {
        std::cout << "Vector vData: " << v.vData << "   Vector Name: " << v.className << std::endl;
    }
    std::cout << "###############################################" << std::endl;

    Select select(resultVector, k);
    select.calculate();

    int sizeToDelete = resultVector.size();
    while(k < sizeToDelete) {
        resultVector.pop_back();
        sizeToDelete--;
    }
    for (DistanceVec v : resultVector) {
        std::cout << "Vector vData: " << v.vData << "   Vector Name: " << v.className << std::endl;
    }

    std::map<std::string, int> counter;
    for(DistanceVec v : resultVector) {
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
    std::map<std::string, int>::iterator itMax = counter.begin();
    // getting the max value from the map
    for(std::map<std::string, int>::iterator it=counter.begin(); it != counter.end(); ++it) {
        // setting new max
        if(itMax->second < it->second) {
            itMax = it;
        }
    }

    std::cout << "\nMaximum value appeared is: " << itMax->first << std::endl;
    knnClassified = itMax->first;
}