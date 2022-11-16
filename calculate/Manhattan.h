//
// Created by shilo on 16/11/2022.
//

#ifndef MAIN_CPP_MANHATTAN_H
#define MAIN_CPP_MANHATTAN_H
#include "Distance.h"

class Manhattan : public Distance {

public:
    double operator()(std::vector<double> v1, std::vector<double> v2) override;

};
#endif //MAIN_CPP_MANHATTAN_H
