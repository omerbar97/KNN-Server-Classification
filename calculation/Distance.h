//
// Created by omerb on 12/11/2022.
//

#ifndef ADVANCED_PROGRAMMING_DISTANCE_H
#define ADVANCED_PROGRAMMING_DISTANCE_H

//includes files:
#include <vector>
#include <cmath>

/**
 * Class that hold all the function that calculates all the kind of distance between two vectors.
 * this class only calculate, therefore it shouldn't have an instance.
 **/
class Distance {

private: //private function here:

    Distance() = delete;
    /**
     * this function takes two vectors and for each element in the vector it calculate |x1 - x2|
     * and assign it to the result vector.
     **/
    static std::vector<double> absVector(std::vector<double> v1, std::vector<double> v2);

public: //public function here:

    /**
     * In mathematics, the Euclidean distance between two points in Euclidean space is the
     * length of a line segment between the two points.
     * link: https://en.wikipedia.org/wiki/Euclidean_distance
     * **/
    static double Euclidean(std::vector<double> v1, std::vector<double> v2);

    /**
    * A taxicab geometry or a Manhattan geometry is a geometry in which the usual distance function
    * or metric of Euclidean geometry is replaced by a new metric in which the distance between two
    * points is the sum of the absolute differences of their Cartesian coordinates.
    * link: https://en.wikipedia.org/wiki/Taxicab_geometry
    * **/
    static double Manhattan(std::vector<double> v1, std::vector<double> v2);

    /**
    * In mathematics, Chebyshev distance (or Tchebychev distance), maximum metric, or L∞ metric[1]
    * is a metric defined on a vector space where the distance between two vectors is the greatest
    * of their differences along any coordinate dimension
    * link: https://en.wikipedia.org/wiki/Chebyshev_distance
    * **/
    static double Chebyshev(std::vector<double> v1, std::vector<double> v2);

    /**
    * The Canberra distance is a numerical measure of the distance between pairs of points in a vector space,
    * link: https://en.wikipedia.org/wiki/Canberra_distance
    * **/
    static double Canberra(std::vector<double> v1, std::vector<double> v2);

    /**
    * The Minkowski distance or Minkowski metric is a metric in a normed vector space which can be considered
    * as a generalization of both the Euclidean distance and the Manhattan distance.
    * link: https://en.wikipedia.org/wiki/Minkowski_distance
    * **/
    static double Minkowski(std::vector<double> v1, std::vector<double> v2);


};
#endif //ADVANCED_PROGRAMMING_DISTANCE_H
