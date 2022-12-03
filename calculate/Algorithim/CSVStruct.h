//
// Created by omerb on 02/12/2022.
//

#ifndef RUNNABLE_CSVSTRUCT_H
#define RUNNABLE_CSVSTRUCT_H

/**
 * DistanceVec struct
 * double vData - store the distance between some vector v1 to some inputVector.
 * std::string hold the vector classified name tag.
 */
struct DistanceVec{
    double vData;
    std::string className;
};

/**
 * VectorCSV struct
 * std::vector<double> hold the vector value.
 * std::string hold the classified name of the vector tag.
 */
struct VectorCSV {
    std::vector<double> id;
    std::string name;
};


#endif //RUNNABLE_CSVSTRUCT_H
