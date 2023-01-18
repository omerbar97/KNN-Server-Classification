//
// Created by oem on 1/14/23.
//

#include "AlgorithemSettingServerCommand.h"



AlgorithemSettingServerCommand::AlgorithemSettingServerCommand(DefaultIO &io, int k) : ICommand(io){
    this->description = "2. algorithm setting\n";
    this->k = k;
    this->metric = "EUC";
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
            try {
                k = atoi(s.c_str());
            }catch (std::invalid_argument a) {
                result = 1;
            }
        }
        if (counter == 2) {
            if(s == "MIN") {
                newMetric = "MIN";
            } else if( s == "EUC") {
                newMetric == "EUC";
            } else if (s == "CAN") {
                newMetric = "CAN";
            } else if (s == "CHB") {
                newMetric = "CHB";
            } else if (s == "AUC") {
                newMetric == "AUC";
            } else {
                if (result == 1) {
                    return 3;
                } else {
                    return 2;
                }
            }
        }
    }

    if (counter != 2) {
        return 3;
    }
    if ( result == 0) {
        this->k = k;
        this->metric = newMetric;
    }
    return result;
}

void AlgorithemSettingServerCommand::execute() {
    //server send the current parameters
    std::string message;
    std::stringstream mess;
    mess << "The current KNN parameters are: K = "<< this->k << ", distance metric = " << this->metric;
    io.write(mess.str());

    std::string parameters;
    parameters = io.read();

    //if user want the same parameters return
    if (parameters == "\n") {
        return;
    }

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
    }
    //nowe we sure that the parameters are valid so here we after updaiting the parameter.
    // close the program

}

AlgorithemSettingServerCommand::~AlgorithemSettingServerCommand() {

}

