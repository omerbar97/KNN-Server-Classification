//
// Created by omerb on 02/12/2022.
//

#ifndef RUNNABLE_CSVSTRUCT_H
#define RUNNABLE_CSVSTRUCT_H

/**
 * creating struct to hold the distance data.
 */
struct DistanceVec{
    double vData;
    std::string className;
};

struct VectorCSV {
    std::vector<double> id;
    std::string name;
};


#endif //RUNNABLE_CSVSTRUCT_H
