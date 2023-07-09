#include "Manhattan.h"

double Manhattan::operator()(std::vector<double> v1, std::vector<double> v2){
    if(v1.size() != v2.size()) {
        return -1; // in case the vector not in the same size.
    }
    double result = 0;
    std:: vector<double> vec = absVector(v1, v2);
    for (int i = 0; i < vec.size(); i++) {
        result += vec[i];
    }
    return result;
}
