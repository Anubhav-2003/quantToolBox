#include "RelativeStrengthIndexStrategy.h"
#include <iostream>
#include <fstream>
#include <numeric>
#include <algorithm>

RelativeStrengthIndexStrategy::RelativeStrengthIndexStrategy(int rsiPeriod, double overboughtThreshold, double oversoldThreshold)
    : period(rsiPeriod), overbought(overboughtThreshold), oversold(oversoldThreshold) {}

std::vector<double> RelativeStrengthIndexStrategy::calculateRSI(const std::vector<double>& prices, int period) {
    std::vector<double> rsi;

    if (prices.size() < period + 1) return rsi;

    std::vector<double> changes(prices.size(), 0.0);
    for (size_t i = 1; i < prices.size(); ++i) {
        changes[i] = prices[i] - prices[i - 1];
    }

    std::vector<double> gains(prices.size(), 0.0);
    std::vector<double> losses(prices.size(), 0.0);
    for (size_t i = 1; i < prices.size(); ++i) {
        if (changes[i] > 0) {
            gains[i] = changes[i];
        } else {
            losses[i] = -changes[i];
        }
    }

    double avgGain = std::accumulate(gains.begin() + 1, gains.begin() + period + 1, 0.0) / period;
    double avgLoss = std::accumulate(losses.begin() + 1, losses.begin() + period + 1, 0.0) / period;

    rsi.push_back(100 - (100 / (1 + avgGain / avgLoss)));

    for (size_t i = period + 1; i < prices.size(); ++i) {
        avgGain = (avgGain * (period - 1) + gains[i]) / period;
        avgLoss = (avgLoss * (period - 1) + losses[i]) / period;

        if (avgLoss == 0) {
            rsi.push_back(100);
        } else {
            double rs = avgGain / avgLoss;
            rsi.push_back(100 - (100 / (1 + rs)));
        }
    }

    return rsi;
}

void RelativeStrengthIndexStrategy::execute(const std::vector<double>& prices) {
    std::vector<double> mutablePrices = prices;
    std::reverse(mutablePrices.begin(), mutablePrices.end());

    if (mutablePrices.size() < period) {
        std::cerr << "Error: Not enough data for the strategy\n";
        return;
    }

    auto rsiValues = calculateRSI(mutablePrices, period);

    bool position = false;

    std::ofstream outFile("./csv/rsi_strategy_output.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file\n";
        return;
    }

    outFile << "Index,Price,RSI,Action\n";
    for (size_t i = 0; i < rsiValues.size(); ++i) {
        size_t priceIndex = i + period - 1;

        if (rsiValues[i] < oversold && !position) {
            std::cout << "Buy at price: " << mutablePrices[priceIndex] << " (RSI: " << rsiValues[i] << ")\n";
            outFile << priceIndex << "," << mutablePrices[priceIndex] << "," << rsiValues[i] << ",Buy\n";
            position = true;
        } else if (rsiValues[i] > overbought && position) {
            std::cout << "Sell at price: " << mutablePrices[priceIndex] << " (RSI: " << rsiValues[i] << ")\n";
            outFile << priceIndex << "," << mutablePrices[priceIndex] << "," << rsiValues[i] << ",Sell\n";
            position = false;
        }
    }

    outFile.close();
}
