//
// Created by oem on 1/17/23.
//

#include "ServerCommands.h"
#include <mutex>

//std::mutex mutex;
//
//ServerCommands* ServerCommands::instance = NULL;

ServerCommands::ServerCommands() : metric("EUC"), k(5) {

}

//ServerCommands*  ServerCommands::getInstance() {
//    std::lock_guard<std::mutex> myLock(mutex);
//    if(!instance) {
//        ServerCommands::instance = new ServerCommands();
//    }
//    return instance;
//}
void ServerCommands::setK(int k) {
    this->k = k;
}
void ServerCommands::setMetric(std::string string){
    this->metric = string;
}


int ServerCommands::getK(){
    return this->k;
}
std::string ServerCommands::getMetric() {
    return this->metric;
}

ServerCommands::~ServerCommands() {
//    delete(instance);
}
