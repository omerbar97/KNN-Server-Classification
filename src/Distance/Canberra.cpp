//
// Created by shilo on 16/11/2022.
//
#include "Canberra.h"

double Canberra::operator()(std::vector<double> v1, std::vector<double> v2) {
    if(!Distance::checkVectors(v1, v2)) {
        return -1; // in case the vector not in the same size.
    }
    double result = 0, fact;
    std::vector<double> vec = absVector(v1, v2);
    for (int i = 0; i < vec.size(); i++) {
        fact = std::abs(v1[i]) + std::abs(v2[i]);
        if(fact != 0) {
            result += vec[i] / (fact);
        }
    }
    return result;
}



