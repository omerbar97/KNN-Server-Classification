//
// Created by omerb on 16/11/2022.
//

#ifndef ADVANCED_PROGRAMMING_DISTANCE_H
#define ADVANCED_PROGRAMMING_DISTANCE_H
#include <vector>
#include <type_traits>
#include <cmath>

class Distance {
protected:

    /**
     * check if two giving vector can be added/multi. check if the size is the same.
     * @param v1 - vector type T generic
     * @param v2 - vector type T generic
     * @return
     */
    bool checkVectors(std::vector<double> v1, std::vector<double> v2);

    /**
     * this function takes two vectors and for each element in the vector it calculate |x1 - x2|
     * and assign it to the result vector.
     * @param v1
     * @param v2
     * @return
     */
    std::vector<double> absVector(std::vector<double> v1, std::vector<double> v2);

public:

    /**
     * for each algorithm that going to inheritance the distance class, need's to implements the
     * calculation algorithm.
     * @param v1 - vector type T generic
     * @param v2 - vector type F generic
     * @return return the distance between them.
     */
    virtual double operator()(std::vector<double> v1, std::vector<double> v2) = 0;



};



#endif //ADVANCED_PROGRAMMING_DISTANCE_H
