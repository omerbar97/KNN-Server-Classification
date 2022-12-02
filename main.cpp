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
    int vecLen = strVec.size();
    for (int i = 0 ; i < vecLen ; i++) {
        std::string correctString = strVec[i];
        std::string::const_iterator iterator = correctString.begin();
        //iterate all over the characters.
        while (iterator != correctString.end() && (std ::isdigit(*iterator) || *iterator == '.')) {
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
    string dot = ".";
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

int main() {
    std::vector<double> v = {1, 2, 3};
    std::vector<double> vVector = {1, 1, 3};
    std::vector<double> vVector2 = {5, 2, 15};
    std::vector<double> vVector3 = {19, 17, 19};
    std::vector<double> vVector4 = {12, 15, 2};
    std::vector<double> vVector5 = {1, 22, 33};


    VectorCSV vCSV = {vVector, "name-1"};
    VectorCSV vCSV2 = {vVector2, "name-2"};
    VectorCSV vCSV3 = {vVector3, "name-3"};
    VectorCSV vCSV4 = {vVector4, "name-4"};
    VectorCSV vCSV5 = {vVector5, "name-5"};

    std::vector<VectorCSV> vv;
    vv.push_back(vCSV);
    vv.push_back(vCSV2);
    vv.push_back(vCSV3);
    vv.push_back(vCSV4);
    vv.push_back(vCSV5);

    Distance* euc = new Euclidean();

    Knn kTest(v, vv, euc, 1);
    std::cout << kTest.getClassified() << std::endl;
    kTest.setK(2);
    kTest.calculate();
    std::cout << kTest.getClassified() << std::endl;
    kTest.setK(3);
    kTest.calculate();
    std::cout << kTest.getClassified() << std::endl;
    kTest.setK(4);
    kTest.calculate();
    std::cout << kTest.getClassified() << std::endl;
    kTest.setK(5);
    kTest.calculate();
    std::cout << kTest.getClassified() << std::endl;

//    std::string vec1;
//    std::string vec2;
//    string input;
//
//    getline(cin, vec1);
//    getline(cin, vec2);
//    checkPropriety(vec1, vec2);
//    if (!checkPropriety(vec1, vec2)) {
//        // the string is holding invalid value. a.k.a. not a number or the vector not in the same size.
//        std::cout << "Incorrect input, Please make sure the vectors are in the same size and " <<
//                  "they are only numeric value." << std::endl;
//        return 0; // exit the program.
//    }
//
//    // creating a vector from the string;
//
//    std::vector<std::string> vString1 = splitString(vec1);
//    std::vector<std::string> vString2 = splitString(vec2);
//
//    //converting to vector type double
//
//    std::vector<double> v1 = convertStrVecToDoubleVec(vString1);
//    std::vector<double> v2 = convertStrVecToDoubleVec(vString2);
//
//    // initializing the distance array.
//
//    Euclidean euclidean;
//    Minkowski minkowski;
//    Manhattan manhattan;
//    Chebyshev chebyshev;
//    Canberra canberra;
//    std::vector<Distance *> distance;
//
//
//
//    // assign the array
//
//    distance.push_back(&euclidean);
//    distance.push_back(&manhattan);
//    distance.push_back(&chebyshev);
//    distance.push_back(&canberra);
//    distance.push_back(&minkowski);
//
//    // print format
//    std::cout << std::fixed;
//
//    // printing the result
//
//    double result;
//
//    for (int i = 0; i < distance.size(); i++) {
//
//
//        result = (*distance[i])(v1, v2); // calculate each distance.
//        // in case the result is an integer prints the number like that x.0 for example 5.0
//        if (result == (int) result) {
//            std::cout.precision(1);
//        }
//        // in case the number is a double then prints it with 17 digits after the point.
//        else {
//            std::cout.precision(16);
//        }
//        std::cout << result << std::endl;
//    }
    return 0;
}
