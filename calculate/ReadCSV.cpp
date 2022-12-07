#include "ReadCSV.h"

ReadCSV::ReadCSV(std::string fileName) {
    this->fileName = fileName;
    csvToData();
}

void ReadCSV::csvToData() {
    std::vector<double> id;
    std::string line, word,name;
    VectorCSV singleData;
    std::vector<VectorCSV> vectorData;
    float d;
    std::fstream file(fileName, std::ios::in);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            id.clear();
            std::stringstream str(line);
            // getting the number until string appears
            while (std::getline(str, word, ',')) {
                try {
                    d = std::stod(word);
                    id.push_back(d);
                } catch(std::exception d) {
                    singleData.name = word;
                    singleData.id = id;
                }
            }
            // pushing the vectorCSV struct into the vectorData.
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
                std::cout << "tag-name:" << data[i].name<<", values: ";
            }
            std::cout<<data[i].id[j];
            if (j != data[i].id.size()) {
                std::cout<<", ";
            }
        }
    }
    std::cout << "\n";
}
