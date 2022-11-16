//
// Created by shilo on 16/11/2022.
//

#ifndef MAIN_CPP_MANHATTAN_H
#define MAIN_CPP_MANHATTAN_H
#include "Distance.h"

class Manhattan : public Distance {

public:
    /**
    * A taxicab geometry or a Manhattan geometry is a geometry in which the usual distance function
    * or metric of Euclidean geometry is replaced by a new metric in which the distance between two
    * points is the sum of the absolute differences of their Cartesian coordinates.
    * link: https://en.wikipedia.org/wiki/Taxicab_geometry
    **/
    double operator()(std::vector<double> v1, std::vector<double> v2) override;

};
#endif //MAIN_CPP_MANHATTAN_H
