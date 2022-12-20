//
// Created by omerb on 16/11/2022.
//

#include "Euclidean.h"

double Euclidean::operator()(std::vector<double> v1, std::vector<double> v2) {
    if(!Distance::checkVectors(v1, v2)) {
        return -1; // in case the vector not in the same size.
    }
    double result = 0;
    std::vector<double> calc(absVector(v1, v2));
    for(double d : calc) {
        result += std::pow(d, 2);
    }
    return std::sqrt(result);
}


