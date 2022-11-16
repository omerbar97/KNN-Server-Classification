

#include "Chebyshev.h"


double Chebyshev::operator()(std::vector<double> v1, std::vector<double> v2) {
    if(v1.size() != v2.size()) {
        return -1; // in case the vector not in the same size.
    }
    std::vector<double> calc(absVector(v1, v2));
    double max = calc[0];
    for (double d : calc) {
        if(max < d) {
            max = d;
        }
    }
    return max;
}
