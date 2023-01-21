//
// Created by oem on 1/14/23.
//

#include "DisplayServerCommand.h"


DisplayServerCommand::DisplayServerCommand(DefaultIO &io) : ICommand(io){
    this->description =  "4. display results\n";

}

DisplayServerCommand::~DisplayServerCommand() {

}

void DisplayServerCommand::execute() {
    std::stringstream message;
    //if not update files yet
    if (this->p_Data->testData == nullptr || this->p_Data->trainData == nullptr) {
        message << "Please upload data\n";
    }
    //if not classified data yet
    else if ( this->p_Data->classifiedResult == nullptr) {
        message << "Please classify the data\n";
    }
    //if we have one of the above problem, send the message and return.
    if (message.rdbuf()->in_avail() != 0) {
        io.write("-1");
        io.write(message.str());
        return;
    }
    io.write("1");

    //otherwise send data to print by cline line by line
    std::string str;
    size_t classifiedDataSize = this->p_Data->classifiedResult->size();
    for (int i = 0; i < classifiedDataSize; ++i) {
        message.str("");
        message << i + 1 << "\t" << this->p_Data->classifiedResult->at(i).c_str() << std::endl;
        io.write(message.str());
    }
    //symbol of end text
    io.write("#");

}