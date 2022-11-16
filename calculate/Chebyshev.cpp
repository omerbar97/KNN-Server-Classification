

#include "Chebyshev.h"


double Chebyshev::operator()(std::vector<double> v1, std::vector<double> v2) {
    if(!Distance::checkVectors(v1, v2)) {
        return -1; // in case the vector not in the same size.
    }
    std::vector<double> vec = absVector(v1 ,v2);
    double max = vec[0];
    for (double d : vec) {
        if(max < d) {
            max = d;
        }
    }
    return max;
}
