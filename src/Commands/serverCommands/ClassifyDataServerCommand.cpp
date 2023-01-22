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
    std::stringstream message;

    if(this->p_Data->testData == nullptr || this->p_Data->trainData == nullptr) {
        io.write("-1");
        io.write("Please upload data\n");
        return;
    }
    else if(this->p_Data->trainData->size() < this->p_Data->k) {
        // k cannot be greater than the number of vector in file
        io.write("-1");
        message << "Please change the number \"k\" in the Knn algorithm, K cannot be greater then the size of the trained file\n";
        message << "currently K = " << this->p_Data->k << " and the trained vector size = " << this->p_Data->trainData->size() << std::endl;
        io.write(message.str());
        return;
    }
    // everything okay with the setting
    io.write("1");
    auto* newClassify = new std::vector<std::string>;

    // setting Knn:
    Knn* knn = new Knn(*this->p_Data->trainData);
    Knn& KNN = *knn;
    KNN.setK(this->p_Data->k);
    Distance* metric = input::getDistance(p_Data->metric);
    KNN.setDistance(metric);

    size_t size = this->p_Data->testData->size();
    for(int i = 0; i < size; i++){
        KNN.setVector(this->p_Data->testData->at(i));
        KNN.calculate();
        newClassify->push_back(KNN.getClassified());
    }
    this->p_Data->classifiedResult = newClassify;

    io.write("complete data classifying\n");
    //we will classify the data

    delete(metric);
    delete(knn);
}
ClassifyDataServerCommand::~ClassifyDataServerCommand() noexcept {

}




