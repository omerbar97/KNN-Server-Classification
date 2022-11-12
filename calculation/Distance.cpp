//
// Created by shilo on 12/11/2022.
//
#include "Distance.h"

std::vector<double> Distance::absVector(std::vector<double> v1, std::vector<double> v2) {
    std::vector<double> calc;
    unsigned max = v1.size();
    for(int i = 0; i < max; i++) {
        calc.push_back(std::abs(v1[i] - v2[i]));
    }
    return calc;
}
double Distance::Manhattan(std::vector<double> v1, std::vector<double> v2) {
    double result = 0;
    std:: vector<double> vec = absVector(v1, v2);
    for (int i = 0; i < v1.size() ; i++) {
        result += vec[i];
    }
    return result;
}
double Distance :: Canberra(std::vector<double> v1, std::vector<double> v2) {
    double result = 0;
    std:: vector<double> vec = absVector(v1, v2);
    for (int i = 0; i < v1.size() ; i++) {
        result += vec[i] / (std::abs(v1[i])+std::abs(v2[i]));
    }
    return result;
}


