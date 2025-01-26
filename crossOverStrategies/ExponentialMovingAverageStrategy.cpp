#include "ExponentialMovingAverageStrategy.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>

ExponentialMovingAverageStrategy::ExponentialMovingAverageStrategy(int shortW, int longW)
    : shortWindow(shortW), longWindow(longW) {}

std::vector<double> ExponentialMovingAverageStrategy::calculateExponentialMovingAverage(const std::vector<double>& prices, int window) {
    std::vector<double> ema;

    if (prices.size() < window) return ema;

    double multiplier = 2.0 / (window + 1);

    double initialSMA = std::accumulate(prices.begin(), prices.begin() + window, 0.0) / window;
    ema.push_back(initialSMA);

    for (size_t i = window; i < prices.size(); ++i) {
        double value = (prices[i] - ema.back()) * multiplier + ema.back();
        ema.push_back(value);
    }

    return ema;
}

void ExponentialMovingAverageStrategy::execute(const std::vector<double>& prices) {
    std::vector<double> mutablePrices = prices;

    std::reverse(mutablePrices.begin(), mutablePrices.end());

    if (mutablePrices.size() < longWindow) {
        std::cerr << "Error: Not enough data for the strategy\n";
        return;
    }

    auto shortEMA = calculateExponentialMovingAverage(mutablePrices, shortWindow);
    auto longEMA = calculateExponentialMovingAverage(mutablePrices, longWindow);

    bool position = false;

    std::ofstream outFile("./csv/ema_strategy_output.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file\n";
        return;
    }

    outFile << "Index,Price,Action\n";
    for (size_t i = 0; i < longEMA.size(); ++i) {
        size_t priceIndex = i + longWindow - 1;

        if (shortEMA[i + longWindow - shortWindow] > longEMA[i] && !position) {
            std::cout << "Buy at price: " << mutablePrices[priceIndex] << "\n";
            outFile << priceIndex << "," << mutablePrices[priceIndex] << ",Buy\n";
            position = true;
        } else if (shortEMA[i] < longEMA[i] && position) {
            std::cout << "Sell at price: " << mutablePrices[priceIndex] << "\n";
            outFile << priceIndex << "," << mutablePrices[priceIndex] << ",Sell\n";
            position = false;
        }
    }

    outFile.close();
}
