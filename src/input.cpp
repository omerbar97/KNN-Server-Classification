//
// Created by omerb on 20/12/2022.
//

#include "input.h"

/**
 * This function get a String and split the string to a vector by the delimiter of space.
 * @param str String.
 * @return Vector<string>.
 */
std::vector<std::string> input::splitString(std::string str) {
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
bool input::isContainChar(std::vector<std::string> strVec) {
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
std::vector<double> input::convertStrVecToDoubleVec(std::vector<std::string> strVec) {
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
        catch (std::invalid_argument &argument) {
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
bool input::checkPropriety(std::string v1, std::string v2) {
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

/**
 * given a string checks if the string hold only numeric value (can hold spaces between)
 * @param v - std::string
 * @return - True if the string is only number. False otherwise.
 */
bool input::checkVectorInput(std::string v) {
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


/**
 * getting the An distance algorithm from string.
 * @param input - string: AUC or MAN or CHB or CAN or MIN
 * @return Pointer to the distance algorithm.
 */
Distance* input::getDistance(std::string input) {
    if(input.compare("AUC") == 0) {
        return new Euclidean();
    }
    if(input.compare("MAN") == 0) {
        return new Manhattan();
    }
    if(input.compare("CHB") == 0) {
        return new Chebyshev();
    }
    if(input.compare("CAN") == 0) {
        return new Canberra();
    }
    if(input.compare("MIN") == 0) {
        return new Minkowski();
    }
    return nullptr;
}

/**
 * Getting a message then an output stream and print the message inside the stream.
 * defalut stream is std::cout ; the output stream MUST override operator<<
 * @param message - std::string
 * @param stream - std::ostream&
 */
void input::print(const std::string& message, std::ostream &stream, const std::string& end) {
    stream << message << end;
}

/**
 * A const message to print an error in the screen, the default stream is std::cout ;
 * the output stream MUST override operator<<
 * @param stream - std::ostream&
 */
void input::error(std::ostream &stream) {
    input::print("invalid input!", stream);
}


/**
 * This function convert from string to char* array.
 * @param s std::string s.
 * @return char *.
 */
char* input::strToChrArray(std::string s) {
    char * data = new char [s.size()];
    for(int i = 0 ; i < s.size() ; i++) {
        data[i] = s[i];
    }
    return data;
}

bool input::checkFilePath(std::string filePath) {
    std::fstream file(filePath, std::ios::in);
    if(file.is_open()) {
        return true;
    }
    return false;

}