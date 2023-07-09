//
// Created by omer on 1/13/23.
//

#include "UploadFilesServerCommand.h"



UploadFilesServerCommand::UploadFilesServerCommand(DefaultIO &io) : ICommand(io){
    this->description = "1. upload an unclassified csv data file\n";

}

/**
 * This function get a string and convert this line to vectorCSV, that contain double and string.
 * @param line ,string
 * @return VectorCSV
 */

VectorCSV lineToVectorCSV(std::string line) {
    std::string word;
    std::vector<double> id;
    std::stringstream str(line);
    float d;
    int counter = 0;
    bool isValidLine = false;
    VectorCSV singleData;

    while (std::getline(str, word, ',')) { // 1.5 3 4 5
        counter++;
        try {
            //it's a number so push it to the vector
            d = std::stod(word);
            id.push_back(d);
        } catch(std::exception d) {
            //if it's not a number then push it as the name of the vector
            singleData.className = word;
            singleData.id = id;
            isValidLine = true;
        }
    }
    if(!isValidLine) {
        // not an legal line
        singleData.id.clear();
    }
    return singleData;

}
/**
 * This function get a string , and splite the string to a vector of number.
 * if the string contain nin number type, return empty vector.
 * @param line , string.
 * @return vector<double>, if fail return {}
 */
std::vector<double> lineToVectorTest(std::string line) {
    std::string word;
    std::vector<double> vector;
    std::stringstream str(line);
    float d;

    while (std::getline(str, word, ',')) { // 1.5 3 4 5
        try {
            //it's a number so push it to the vector
            d = std::stod(word);
            vector.push_back(d);
        } catch(std::exception d) {
            return {};
        }
    }
    return vector;
}

void UploadFilesServerCommand::execute() {
    // all the logics to get user locally file for trainer and second file for classified.
    // getting the user first trained file locally on computer this function will be called from the server side.
    io.write("Please upload your local train CSV file.\n");
    // creating new folder for the client locally files.
    bool isValid = true;
    std::string dataRec, check;
    check = io.read();
    if(check == "-1") {
        // error from client
        return;
    }
    auto* trainData = new std::vector<VectorCSV>;

    //read all lines from client
    dataRec = io.read();
    while (dataRec != "#") {
        //pushing lines to vector
        VectorCSV v = lineToVectorCSV(dataRec);
        if(v.id.empty()) {
            // error not in the exact format
            isValid = false;
        }
        trainData->push_back(v);
        dataRec = io.read();
    }

    if(!isValid) {
        io.write("-1"); // not valid
        io.write("Incorrect train file format.\n");
        delete(trainData);
        return;
    }
    io.write("1"); // valid

    // sending to client Upload succeed.
    io.write("Upload Succeed\n");


    // uploading test file.
    io.write("Please upload your local test CSV file.\n");

    auto* testData = new std::vector<std::vector<double>>;

    //read all lines from client
    dataRec = io.read();
    while (dataRec != "#") {
        //pushing lines to vector
        std::vector<double> v = lineToVectorTest(dataRec);
        if(v.empty()) {
            isValid = false;
        }
        testData->push_back(v);
        dataRec = io.read();
    }

    if(!isValid) {
        io.write("-1"); // not valid
        io.write("Incorrect test file format.\n");
        delete(testData);
        delete(trainData);
        return;
    }
    io.write("1"); // valid


    //checking if the test file and train file in the same size.
    if(testData->at(0).size() != trainData->at(0).id.size()) {
        // incompatible files
        io.write("-1");
        io.write("Incompatible file, please check that the files contains vector in the same length.\n");
        delete(testData);
        delete(trainData);
        return;
    }

    io.write("1"); // file okay

    // deleting old files.
    if(this->p_Data->testData != nullptr) {
        delete(this->p_Data->testData);
    }
    if(this->p_Data->trainData != nullptr) {
        delete(this->p_Data->trainData);
    }

    this->p_Data->testData = testData;
    this->p_Data->trainData = trainData;

    io.write("Upload Succeed\n");

}


UploadFilesServerCommand::~UploadFilesServerCommand() {

}
