//
// Created by oem on 1/14/23.
//

#include "AlgorithemSettingServerCommand.h"



AlgorithemSettingServerCommand::AlgorithemSettingServerCommand(DefaultIO &io, int k) : ICommand(io){
    this->description = "2. algorithm settings\n";
}


int AlgorithemSettingServerCommand::tokenize(std::string const &str, const char delim,std::vector<std::string> &out){
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    int result = 0, counter = 0;

    int k;
    std::string newMetric;
    std::size_t distancePos;
    while (std::getline(ss, s, delim)) {
        counter++;
        if (counter == 1) {
            k = atoi(s.c_str());
            if (k == 0) {
                result = 1;
            }
        }
        if (counter == 2) {
            if(s == "MIN") {
                newMetric = "MIN";
            } else if( s == "EUC") {
                newMetric = "EUC";
            } else if (s == "CAN") {
                newMetric = "CAN";
            } else if (s == "CHB") {
                newMetric = "CHB";
            } else if (s == "AUC") {
                newMetric = "AUC";
            } else {
                if (result == 1) {
                    result = 3;
                } else {
                    result = 2;
                }
            }
        }
    }

    if (counter != 2) {
        return 4;
    }
    if (result == 0) {
        this->p_Data->k = k;
        this->p_Data->metric = newMetric;
    }
    return result;
}

void AlgorithemSettingServerCommand::execute() {
    //server send the current parameters
    std::string message;
    std::stringstream mess;
    mess << "The current KNN parameters are: K = " << this->p_Data->k << ", distance metric = " << this->p_Data->metric;
    io.write(mess.str());

    std::string enter;
    std::string parameters;
    enter = io.read();
    if(enter.compare("#") == 0) {
        // no need to change settings
        return;
    }


    parameters = io.read();

    //if user want to change parameters

    const char delim = ' ';
    std::vector<std::string> out;

    //function that check if the input is valid and update the data;
    int check = tokenize(parameters, delim, out);

    //if the input is invalid we split the cases what part of the input is invalid.
    if(check) {
        if (check == 3) {
            io.write("Invalid value for metric\ninvalid value for K\n");
            return;
        }
        if (check == 1) {
            io.write("invalid value for K\n");
            return;
        }
        if (check == 2) {
            io.write("Invalid value for metric\n");
            return;
        }
        io.write("Incorrect format![k metric].\n");
        return;
    }
    //now we sure that the parameters are valid so here we after update the parameter.
    mess.str("");
    mess << "Algorithm setting changed: K = "<< this->p_Data->k << ", distance metric = " << this->p_Data->metric<<std::endl;
    io.write(mess.str());


}

AlgorithemSettingServerCommand::~AlgorithemSettingServerCommand() {

}

