//
// Created by oem on 1/17/23.
//

#ifndef A_OUT_SERVERCOMMANDS_H
#define A_OUT_SERVERCOMMANDS_H

#include "../CLI.h"
class ServerCommands {

public:

    int k;
    std::string metric;
    ServerCommands();
    ~ServerCommands();
    void setK(int k);
    void setMetric(std::string string);
    int getK();
    std::string getMetric();

};
//class ServerCommands: public CLI {
//private:
//    static ServerCommands* instance;
//    std::string metric;
//
//public:
//    int k;
//    static ServerCommands* getInstance();
//    ~ServerCommands();
//    void setK(int k);
//    void setMetric(std::string string);
//    int getK();
//    std::string getMetric();
//
//};

#endif //A_OUT_SERVERCOMMANDS_H
