//
// Created by omerb on 16/11/2022.
//

#ifndef ADVANCED_PROGRAMMING_MINKOWSKI_H
#define ADVANCED_PROGRAMMING_MINKOWSKI_H
#include "Distance.h"

class Minkowski : public Distance {

public:
    /**
    * The Minkowski distance or Minkowski metric is a metric in a normed vector space which can be considered
    * as a generalization of both the Euclidean distance and the Manhattan distance.
    * link: https://en.wikipedia.org/wiki/Minkowski_distance
    **/
    double operator()(std::vector<double> v1, std::vector<double> v2) override;

};


#endif //ADVANCED_PROGRAMMING_MINKOWSKI_H
