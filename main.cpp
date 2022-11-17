//
// Created by shilo on 12/11/2022.
//
#include <iostream>
#include <string>
#include "calculate/Distance.h"
#include "calculate/Euclidean.h"
#include "calculate/Minkowski.h"
#include "calculate/Canberra.h"
#include "calculate/Chebyshev.h"
#include "calculate/Manhattan.h"


using namespace std;
/**
 * This function get a String and split the string to a vector by the delimiter of space.
 * @param str String.
 * @return Vector<string>.
 */
std::vector<std::string> splitString(std::string str) {
    std::vector<std::string> result;
    std::string delimiter  = " ", token;
    size_t position = 0;
    while ((str.find(delimiter) != std::string::npos)) {
        //taking the substring from starting position to the delimiter position.
        position = str.find(delimiter);
        token = str.substr(0, position);
        result.push_back(token);
        str.erase(0, position + delimiter.size());
        token = str;
    }
    result.push_back(token);
    return result;
}
/**
 * This function convert string vector to double vector.
 * if the strings are possible to be converted then the double vector will return,
 * otherwise(there a string that not include numbers) its will return a null vector.
 * @param strVec vector<string>.
 * @return vector<double>.
 */
std::vector<double> convertStrVecToDoubleVec(std::vector<std::string> strVec) {
    std::vector<double> doubleVec;
    int vecLen = strVec.size();
    for (int i = 0 ; i < vecLen ; i++) {
        std::string correctString = strVec[i];
        std::string::const_iterator iterator = correctString.begin();
        while (iterator != correctString.end() && std ::isdigit(*iterator)) {
            ++iterator;
        }
        // is not a number, return empty vec.
        if (iterator != correctString.end()) {
            return {};
        }
        //we sure that this string can be converted to int
        doubleVec.push_back(std::stoi(correctString));
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
    std::vector<std::string>  firstLine = splitString(v1);
    std::vector<std::string>  secondLine = splitString(v2);
    if (firstLine.size() != secondLine.size()) {
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
    std::string vec1;
    std::string vec2;
    string input;

    //std::cout << "Enter vectors: " << std::endl;
    getline(cin, vec1);
    getline(cin, vec2);
    checkPropriety(vec1, vec2);
    if(!checkPropriety(vec1, vec2)) {
        // the string is holding invalid value.
        std::cout << "INVALID INPUT" << std::endl;
        return 0; // exit the program.
    }

    // creating a vector from the string;

    std::vector<std::string> vString1 = splitString(vec1);
    std::vector<std::string> vString2 = splitString(vec2);

    //converting to vector type double

    std::vector<double> v1 = convertStrVecToDoubleVec(vString1);
    std::vector<double> v2 = convertStrVecToDoubleVec(vString2);

    // initializing the distance array.

    Euclidean euclidean;
    Minkowski minkowski;
    Manhattan manhattan;
    Chebyshev chebyshev;
    Canberra canberra;
    std::vector<Distance*> distance;
    //Distance* distance[5];

    // assign the array

    distance.push_back(&euclidean);
    distance.push_back(&manhattan);
    distance.push_back(&chebyshev);
    distance.push_back(&canberra);
    distance.push_back(&minkowski);

    // setting print format precision

    std::cout.precision(17);
    std::cout << std::fixed;

    // printing the result

    for (int i = 0; i < distance.size(); i++) {
        std::cout <<(*distance[i])(v1, v2) << std::endl;
    }

    return 0;
}
