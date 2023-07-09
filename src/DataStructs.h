//
// Created by omer on 1/18/23.
//

#ifndef A_OUT_DATASTRUCTS_H
#define A_OUT_DATASTRUCTS_H
#include <string>
#include <vector>
#include "../server/Server.h"
#include "../client/Client.h"
#include "IO/SocketIO.h"

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
    std::string className;
};

/**
 * std::vector<VectorCSV>* trainData - vector of the data that is already classified;
 * std::vector<std::vector<double>>* testData - vector of the data we want to classify;
 * std::vector<std::string>* classifiedResult;
 * int k - K for the KNN algorithm;
 * int clientId;
 * std::string metric - type of metric in the KNN algorithm;
 * std::string* serverMainIp;
 */
struct clientData{
    std::vector<VectorCSV>* trainData;
    std::vector<std::vector<double>>* testData;
    std::vector<std::string>* classifiedResult;
    int k;
    int clientId;
    std::string metric;
    std::string* serverMainIp;
};

/**
 * ServerData struct;
 * int* clientSocket ;
 * int* clientId;
 * std::string* mainServerIp;
 */
struct ServerData{
    int* clientSocket;
    int* clientId;
    std::string* mainServerIp;
};

/**
 * DownloadFile struct;
 * DefaultIO* io - type of connection;
 * clientData* p_Data;
 * std::string* filePath - name of path to store the result of classified data;
 * Server* server;
 * Client* client;
 */
struct DownloadFile {
    DefaultIO* io;
    clientData* p_Data;
    std::string* filePath;
    Server* server;
    Client* client;
};


#endif //A_OUT_DATASTRUCTS_H

