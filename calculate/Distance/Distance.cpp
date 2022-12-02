//
// Created by omerb on 16/11/2022.
//

#include "Distance.h"

bool Distance::checkVectors(std::vector<double> v1, std::vector<double> v2) {
    if(v1.size() != v2.size()) {
        return false;
    }
    return true;
}


std::vector<double> Distance::absVector(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> calc;
    for(int i = 0; i < v1.size(); i++) {
        calc.push_back(std::abs(v1[i] - v2[i]));
    }
    return calc;
}
