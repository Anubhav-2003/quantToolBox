#include "DataHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

void DataHandler::loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string priceStr;
        if (std::getline(ss, priceStr, ',')) {
            try {
                prices.push_back(std::stod(priceStr));
            } catch (const std::invalid_argument&) {
                std::cerr << "Warning: Skipping invalid data\n";
            }
        }
    }

    file.close();
}

const std::vector<double>& DataHandler::getPrices() const {
    return prices;
}
