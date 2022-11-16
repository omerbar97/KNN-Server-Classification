//
// Created by omerb on 16/11/2022.
//

#ifndef ADVANCED_PROGRAMMING_EUCLIDEAN_H
#define ADVANCED_PROGRAMMING_EUCLIDEAN_H
#include "Distance.h"

class Euclidean : public Distance {

public:
     /**
     * In mathematics, the Euclidean distance between two points in Euclidean space is the
     * length of a line segment between the two points.
     * link: https://en.wikipedia.org/wiki/Euclidean_distance
     **/
    double operator()(std::vector<double> v1, std::vector<double> v2) override;

};


#endif //ADVANCED_PROGRAMMING_EUCLIDEAN_H
