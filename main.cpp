//
// Created by shilo on 12/11/2022.
//
#include <iostream>
#include <string>
#include <cstring>
#include "calculate/Distance/Distance.h"
#include "calculate/Distance/Euclidean.h"
#include "calculate/Distance/Minkowski.h"
#include "calculate/Distance/Canberra.h"
#include "calculate/Distance/Chebyshev.h"
#include "calculate/Distance/Manhattan.h"
#include "calculate/ReadCSV.h"
#include "calculate/Algorithim/Knn.h"

using namespace std;

/**
 * This function get a String and split the string to a vector by the delimiter of space.
 * @param str String.
 * @return Vector<string>.
 */
std::vector<std::string> splitString(std::string str) {
    std::vector<std::string> result;
    std::string delimiter = " ", token;
    size_t position = 0;
    //case that the vector with length 1.
    if((str.find(delimiter)) == std::string::npos){
        token = str;
    }
    while ((str.find(delimiter) != std::string::npos)) {
        //taking the substring from starting position to the delimiter position.
        position = str.find(delimiter);
        token = str.substr(0, position);
        //if there sequences of spaces
        if (!token.empty()) {
            result.push_back(token);
        }
        str.erase(0, position + delimiter.size());
        token = str;
    }
    //if there sequences of spaces
    if (!token.empty()) {
        result.push_back(token);
    }
    return result;
}
/**
 * This function check if there a non-number in the vector string.
 * @param strVec vector of string.
 * @return bool , true-is contain char , false otherwise.
 */
bool isContainChar(std::vector<std::string> strVec) {
    int vecLen = strVec.size(), dotFlag = 0;
    for (int i = 0 ; i < vecLen ; i++) {
        std::string correctString = strVec[i];
        std::string::const_iterator iterator = correctString.begin();
        //iterate all over the characters.
        while (iterator != correctString.end() && (std::isdigit(*iterator) || *iterator == '.')) {
            ++iterator;
        }
        // is not a number, return empty vec.
        if (iterator != correctString.end()) {
            return true;
        }
    }
    return false;
}

/**
 * This function convert string vector to double vector.
 * if the strings are possible to be converted then the double vector will return,
 * otherwise(there a string that not include numbers) its will return a null vector.
 * ( .1 will count as 0.1 and 3. will count as 3.0).
 * @param strVec
 * @return
 */
std::vector<double> convertStrVecToDoubleVec(std::vector<std::string> strVec) {
    std::string dot = ".";
    std::vector<double> doubleVec;
    int vecLen = strVec.size();
    for (int i = 0; i < vecLen; i++) {
        std::string correctString = strVec[i];
        size_t d;
        //try to convert string to double
        try {
            doubleVec.push_back(stod(correctString, (&d)));
        }
        //if there is a problem with converting ,return null.
        catch (std::invalid_argument &argument ) {
            return {};
        }
        catch (std::out_of_range &argument) {

            return {};
        }
    }
    return doubleVec;
}


/**
 * This function get to strings and check if it possible to convert each string to a vector of
 * doubles(by using the function "splitString" and "convertStrVecToDoubleVec")
 * and if the sizes of the vectors are equal.
 * Return true if all the checks get pass and false otherwise.
 * @param v1 string.
 * @param v2 string.
 * @return bool.
 */
bool checkPropriety(std::string v1, std::string v2) {
    std::vector<std::string> firstLine = splitString(v1);
    std::vector<std::string> secondLine = splitString(v2);
    if (firstLine.size() != secondLine.size()) {
        return false;
    }
    if (isContainChar(firstLine) || isContainChar(secondLine)) {
        return false;
    }
    //the size is equal
    std::vector<double> vec1 = convertStrVecToDoubleVec(firstLine);
    std::vector<double> vec2 = convertStrVecToDoubleVec(secondLine);
    if (vec1.empty() || vec2.empty()) {
        return false;
    }
    return true;
}

bool checkVectorInput(std::string v) {
    std::vector<std::string> stringVector = splitString(v);
    if(isContainChar(stringVector)) {
        return false;
    }
    std::vector<double> doubleVector = convertStrVecToDoubleVec(stringVector);
    if(doubleVector.empty()) {
        return false;
    }
    return true;
}

Distance* getDistance(std::string input) {
    if(input.compare("AUC")) {
        return new Euclidean();
    }
    if(input.compare("MAN")) {
        return new Manhattan();
    }
    if(input.compare("CHB")) {
        return new Chebyshev();
    }
    if(input.compare("CAN")) {
        return new Canberra();
    }
    if(input.compare("MIN")) {
        return new Minkowski();
    }
    return nullptr;
}

void printErrorTerminalInput() {
    std::cout << "Incorrect terminal input, please make sure you start the program as follow: \n" <<
              "<exe/out file> <integer k> <CSV_file_to_read> <distance_algorithm>\n" <<
              "Make sure the CSV file is in the program main directory.\n" <<
              "For example: \"a.out 3 iris_classified.csv MAN\"\n" <<
              "List of all distance algorithm:\n" <<
              "\t1.\"AUC\" - Euclidean distance\n" <<
              "\t2.\"MAN\" - Manhattan distance\n" <<
              "\t3.\"CHB\" - Chebyshev distance\n" <<
              "\t4.\"CAN\" - Canberra distance\n" <<
              "\t5.\"MIN\" - Minkowski distance\n" <<
              "------RESTART PROGRAM IS REQUIRED------" << std::endl;
}

void deleteAllocatedMemory() {

}

int main(int argc, char *args[]) {

    if(argc != 4) {
        printErrorTerminalInput();
        return 0;
    }
    // initializing variables.
    // getting data from args:
    std::string result;
    std::string fileName = args[2];
    std::string filePath = "../resources/datasets/" + fileName;
    std::string vInput;
    Distance* distanceAlgo;
    int k;
    // getting data from args
    try {
        // parsing string to int:
        k = std::stoi(args[1]);
    }
    catch (const std::invalid_argument &e) {
        printErrorTerminalInput();
        return 0;
    }

    distanceAlgo = getDistance(args[3]);
    if(distanceAlgo == nullptr) {
        printErrorTerminalInput();
        return 0;
    }
    // getting user input vector
    getline(cin, vInput);
    std::vector<double> v;
    // checking user input:
    if(checkVectorInput(vInput)) {
        // converting the vector into string vector.
        std::vector<std::string> sVector = splitString(vInput);
        // converting the vector into vector of doubles.
        v = convertStrVecToDoubleVec(sVector);

        // read the data from the file
        ReadCSV readCsv(filePath);

        Distance* d = new Manhattan();
        Knn knn(v, readCsv.getData(), d, k);

        if(knn.getClassified().empty()) {
            result = "Couldn't calculate the result, the vector that was inserted was not in the same size"
                     " like every other vector in: " + fileName + " Or in the file there is a vector not "
                                                                  "in the same size.\n";
        }
        else {
            result = knn.getClassified();
        }
    }
    else{
        result = "Couldn't calculate the result, the vector that was inserted was not in the same size"
                 " like every other vector in: " + fileName + " Or in the file there is a vector not "
                                                              "in the same size.\n";
    }

    std::cout << result  << "\n";
    return 0;
}
