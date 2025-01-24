#include "MovingAverageStrategy.h"
#include <iostream>
#include <fstream>
#include <numeric>

MovingAverageStrategy::MovingAverageStrategy(int shortW, int longW)
    : shortWindow(shortW), longWindow(longW) {}

std::vector<double> MovingAverageStrategy::calculateMovingAverage(const std::vector<double>& prices, int window) {
    std::vector<double> movingAverage;
    for (size_t i = 0; i <= prices.size() - window; ++i) {
        double avg = std::accumulate(prices.begin() + i, prices.begin() + i + window, 0.0) / window;
        movingAverage.push_back(avg);
    }
    return movingAverage;
}

void MovingAverageStrategy::execute(const std::vector<double>& prices) {
    if (prices.size() < longWindow) {
        std::cerr << "Error: Not enough data for the strategy\n";
        return;
    }

    auto shortMA = calculateMovingAverage(prices, shortWindow);
    auto longMA = calculateMovingAverage(prices, longWindow);

    bool position = false;

    std::ofstream outFile("strategy_output.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file\n";
        return;
    }

    outFile << "Index,Price,Action\n";

    for (size_t i = 0; i < longMA.size(); ++i) {
        size_t priceIndex = i + longWindow - 1;

        if (shortMA[i] > longMA[i] && !position) {
            std::cout << "Buy at price: " << prices[priceIndex] << "\n";
            outFile << priceIndex << "," << prices[priceIndex] << ",Buy\n";
            position = true;
        } else if (shortMA[i] < longMA[i] && position) {
            std::cout << "Sell at price: " << prices[priceIndex] << "\n";
            outFile << priceIndex << "," << prices[priceIndex] << ",Sell\n";
            position = false;
        }
    }

    outFile.close();
}
