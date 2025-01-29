#include "BollingerBandStrategy.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>
#include <vector>
#include <algorithm>

BollingerBandStrategy::BollingerBandStrategy(int period, double stdDevFactor)
    : period(period), stdDevFactor(stdDevFactor) {}

std::vector<double> BollingerBandStrategy::calculateMovingAverage(const std::vector<double>& prices, int window) {
    std::vector<double> movingAverage;
    if (prices.size() < window) return movingAverage;
    
    for (size_t i = 0; i <= prices.size() - window; ++i) {
        double sum = std::accumulate(prices.begin() + i, prices.begin() + i + window, 0.0);
        movingAverage.push_back(sum / window);
    }
    return movingAverage;
}

std::vector<double> BollingerBandStrategy::calculateStandardDeviation(const std::vector<double>& prices, const std::vector<double>& movingAverage, int window) {
    std::vector<double> stdDev;
    if (prices.size() < window) return stdDev;
    
    for (size_t i = 0; i <= prices.size() - window; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < window; ++j) {
            sum += std::pow(prices[i + j] - movingAverage[i], 2);
        }
        stdDev.push_back(std::sqrt(sum / window));
    }
    return stdDev;
}

void BollingerBandStrategy::execute(const std::vector<double>& prices) {
    std::vector<double> mutablePrices = prices;
    std::reverse(mutablePrices.begin(), mutablePrices.end());

    if (mutablePrices.size() < period) {
        std::cerr << "Error: Not enough data for the strategy\n";
        return;
    }

    auto movingAvg = calculateMovingAverage(mutablePrices, period);
    auto stdDev = calculateStandardDeviation(mutablePrices, movingAvg, period);
    
    std::ofstream outFile("./csv/bollinger_band_strategy_output.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file\n";
        return;
    }
    
    outFile << "Index,Price,Action\n";
    bool position = false;
    
    for (size_t i = 0; i < stdDev.size(); ++i) {
        size_t priceIndex = i + period - 1;
        double upperBand = movingAvg[i] + stdDevFactor * stdDev[i];
        double lowerBand = movingAvg[i] - stdDevFactor * stdDev[i];
        
        if (mutablePrices[priceIndex] < lowerBand && !position) {
            std::cout << "Buy at price: " << mutablePrices[priceIndex] << "\n";
            outFile << priceIndex << "," << mutablePrices[priceIndex] << ",Buy\n";
            position = true;
        } else if (mutablePrices[priceIndex] > upperBand && position) {
            std::cout << "Sell at price: " << mutablePrices[priceIndex] << "\n";
            outFile << priceIndex << "," << mutablePrices[priceIndex] << ",Sell\n";
            position = false;
        }
    }
    
    outFile.close();
}
