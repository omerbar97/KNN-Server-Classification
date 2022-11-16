//
// Created by shilo on 16/11/2022.
//
#include "Canberra.h"
#include <iostream>
double Canberra::operator()(std::vector<double> v1, std::vector<double> v2) {
    if(v1.size() != v2.size()) {
        return -1; // in case the vector not in the same size.
    }
    double result = 0;
    std:: vector<double> vec = absVector(v1, v2);
    for (int i = 0; i < v1.size() ; i++) {
        result += vec[i] / (std::abs(v1[i])+std::abs(v2[i]));
    }
    return result;
}



