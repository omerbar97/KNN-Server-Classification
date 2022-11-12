//
// Created by omerb on 12/11/2022.
//

#include "Distance.h"

/**
 * this function takes two vectors and for each element in the vector it calculate |x1 - x2|
 * and assign it to the result vector.
 **/
 std::vector<double> Distance::absVector(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> calc;
    unsigned max = v1.size();
    for(int i = 0; i < max; i++) {
        calc.push_back(std::abs(v1[i] - v2[i]));
    }
    return calc;
}

 double Distance::Euclidean(std::vector<double> v1, std::vector<double> v2) {
    if(v1.size() != v2.size()) {
        return -1; // in case the vector not in the same size.
    }
    double result = 0;
    std::vector<double> calc(absVector(v1, v2));
    for(double d : calc) {
        result += std::pow(d, 2);
    }
    return std::sqrt(result);
}

double Distance::Minkowski(std::vector<double> v1, std::vector<double> v2) {
    if(v1.size() != v2.size()) {
        return -1; // in case the vector not in the same size.
    }
    int p = 2;
    double _p = (float)1/(float)p;
    double result = 0;
    std::vector<double> calc(absVector(v1, v2));
    for(double d : calc) {
        result += std::pow(d, 2);
    }
    result = std::pow(result, _p);
    return result;
 }






