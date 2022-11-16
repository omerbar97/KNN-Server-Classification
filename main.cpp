//
// Created by shilo on 12/11/2022.
//
//#include "calculation//Distance.h"
#include <iostream>
#include <string>
#include "calculate/Distance.h"
#include "calculate/Euclidean.h"

using namespace std;

int main() {
    std::string vec1;
    std::string vec2;
    string input;

    std::cout << "Enter vectors: " << std::endl;
    getline(cin, vec1);
    getline(cin, vec2);

    //Distance :: checkPropriety("34 23 12" , "9 23 43");

    std::vector<double> v2 = {1, 2, 3};
    std::vector<double> v1 = {3, 2, 1};
//    getline(cin, vec2);
//    double b2 = Distance::manhattan(v1, v2);
//    double b3 = Distance::canberra(v1, v2);
//    std::cout.precision(17);
//    std::cout << b3 ;

    Euclidean calculate;
    Distance* arr[5];
    arr[0] = &calculate;
    double resutl = (arr[0])->operator()(v1, v2);
    //double result = d(v1, v2);
    cout << resutl << endl;

    return 0;
}
