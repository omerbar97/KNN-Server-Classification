//
// Created by oem on 1/16/23.
//

#ifndef A_OUT_CLI_H
#define A_OUT_CLI_H
#include "../../src/Algorithim/CSVStruct.h"
#include <vector>
#include <iostream>
#include <map>
struct clientData{
    std::vector<VectorCSV> trainData;
    std::vector<std::vector<double>> testData;
};

class CLI {

public:
    std::map<int, clientData> data;
    CLI();
    ~CLI() ;
    void start(void);
};

#endif //A_OUT_CLI_H
