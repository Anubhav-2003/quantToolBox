#include "DataHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void DataHandler::loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    std::string line;
    std::vector<std::string> headers;
    int closeIndex = -1;

    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string header;
        int index = 0;
        while (std::getline(ss, header, ',')) {
            headers.push_back(header);
            if (header == "close") {
                closeIndex = index;
            }
            index++;
        }

        if (closeIndex == -1) {
            std::cerr << "Error: 'close' column not found in the header row\n";
            return;
        }
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        int columnIndex = 0;
        double closePrice = 0.0;

        while (std::getline(ss, token, ',')) {
            if (columnIndex == closeIndex) {
                try {
                    closePrice = std::stod(token);
                    prices.push_back(closePrice);
                } catch (const std::invalid_argument&) {
                    std::cerr << "Warning: Skipping invalid close price data\n";
                }
                break;
            }
            columnIndex++;
        }
    }

    file.close();
}

const std::vector<double>& DataHandler::getPrices() const {
    return prices;
}
