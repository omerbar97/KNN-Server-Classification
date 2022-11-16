//
// Created by omerb on 16/11/2022.
//

#include "Minkowski.h"


double Minkowski::operator()(std::vector<double> v1, std::vector<double> v2) {
    if(!Distance::checkVectors(v1, v2)) {
        return 0; // undefined
    }
    int p = 2;
    double _p = (float)1/(float)p;
    double result = 0;
    std::vector<double> calc(absVector(v1, v2));
    for(double d : calc) {
        result += std::pow(d, 2);
    }
    if(result != 0) {
        result = std::pow(result, _p);
    }
    return result;
}
