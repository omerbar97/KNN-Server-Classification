#include "ReadCSV.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

ReadCSV::ReadCSV(std::string fileName) {
    this->fileName = fileName;
    csvToData();
}

void ReadCSV::csvToData() {
    std::vector<double> id;
    std::string line, word,name;
    VectorCSV singleData;
    std::vector<VectorCSV> vectorData;
    int counter;
    std::fstream file(fileName, std::ios::in);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            id.clear();
            std::stringstream str(line);
            counter = 0;
            //we assume that 3 first parameter are number and the forth is string.
            while (std::getline(str, word, ',')) {
                //if we are in the first 3 arg.
                if (counter <= 3) {
                    id.push_back(std::stod(word));
                    counter++;
                    continue;
                }
                singleData.name = word;
                singleData.id = id;
            }
            vectorData.push_back(singleData);
        }
        file.close();
    } else {
        std::cout << "could not open file\n";
    }
    data = vectorData;
}

std::vector<VectorCSV> ReadCSV::getData() {
    return data;
}

void ReadCSV::printCvs() {
    for (int i = 0; i < data.size(); ++i) {
        std::cout<<'\n';
        for (int j = 0; j < data[i].id.size(); ++j) {
            if (j == 0){
                std::cout << data[i].name<<',';
            }
            std::cout<<data[i].id[j];
            if (j != 3) {
                std::cout<<',';
            }
        }
    }
}
