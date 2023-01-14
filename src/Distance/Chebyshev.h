//
// Created by shilo on 16/11/2022.
//

#ifndef MAIN_CPP_CHEBYSHEV_H
#define MAIN_CPP_CHEBYSHEV_H
#include "Distance.h"

class Chebyshev : public Distance {

public:

    /**
    * In mathematics, Chebyshev distance (or Tchebychev distance), maximum metric, or L∞ metric[1]
    * is a metric defined on a vector space where the distance between two vectors is the greatest
    * of their differences along any coordinate dimension
    * link: https://en.wikipedia.org/wiki/Chebyshev_distance
    **/
    double operator()(std::vector<double> v1, std::vector<double> v2) override;

};
#endif //MAIN_CPP_CHEBYSHEV_H
