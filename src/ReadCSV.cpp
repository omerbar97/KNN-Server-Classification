#include "ReadCSV.h"

ReadCSV::ReadCSV(std::string fileName){
    this->fileName = fileName;
    csvToData();
}

void ReadCSV::csvToData() {
    std::vector<double> id;
    std::string line, word,name;
    VectorCSV singleData;
    std::vector<VectorCSV> vectorData;
    float d;
    int lenOfVec = 0, flag = 0, counter = 0;
    std::fstream file(fileName, std::ios::in);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            id.clear();
            std::stringstream str(line);
            // getting the number until string appears
            while (std::getline(str, word, ',')) { // 1.5 3 4 5
                counter++;
                try {
                    d = std::stod(word);
                    id.push_back(d);
                } catch(std::exception d) {
                    singleData.className = word;
                    singleData.id = id;
                }
            }
            if (flag == 0) {
                lenOfVec = counter;
            }
            // if there a line that not the same size with the other
            if (counter != lenOfVec) {
                std::cout << "the folder does not match the format" << std::endl;
                exit(0);
            }
            flag = 1;
            counter = 0;
            if(singleData.className.empty()) {
                singleData.id = id;
            }
            // pushing the vectorCSV struct into the vectorData.
            vectorData.push_back(singleData);
        }
        file.close();
    } else {
        std::cout << "could not open file" << std::endl;
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
                std::cout << "tag-name:" << data[i].className <<", values: ";
            }
            std::cout<<data[i].id[j];
            if (j != data[i].id.size()) {
                std::cout<<", ";
            }
        }
    }
    std::cout << "\n";
}
