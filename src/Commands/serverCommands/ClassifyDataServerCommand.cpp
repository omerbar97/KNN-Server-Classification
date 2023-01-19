//
// Created by oem on 1/14/23.
//

#include "ClassifyDataServerCommand.h"

#include <utility>


ClassifyDataServerCommand::ClassifyDataServerCommand(DefaultIO &io) : ICommand(io) {
    this->description = "3. classify data\n";
}

void ClassifyDataServerCommand::execute() {
    std::string sendData;

    if(this->p_Data->testData.empty() || this->p_Data->trainData.empty()) {
        io.write("-1");
        io.write("Please upload data\n");
        return;
    }
    // everything okay with the setting
    io.write("1");

    // setting Knn:
    Knn* knn = new Knn(this->p_Data->trainData);
    Knn& KNN = *knn;
    KNN.setK(this->p_Data->k);
    Distance* metric = input::getDistance(p_Data->metric);
    KNN.setDistance(metric);

    size_t size = this->p_Data->testData.size();
    for(int i = 0; i < size; i++){
        KNN.setVector(this->p_Data->testData[i]);
        KNN.calculate();
        this->p_Data->classifiedResult.push_back(KNN.getClassified());
    }

    io.write("complete data classifying\n");
    //we will classified the data

    delete(metric);
    delete(knn);
}
ClassifyDataServerCommand::~ClassifyDataServerCommand() noexcept {

}




