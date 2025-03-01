#include "ImpliedVolatility.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

ImpliedVolatility::ImpliedVolatility(double marketPrice, double strike, double timeToMaturity, double riskFreeRate, double spotPrice, double initialGuess)
    : V_market(marketPrice), K(strike), tau(timeToMaturity), r(riskFreeRate), S_0(spotPrice), sigma(initialGuess) {}

double ImpliedVolatility::normalPDF(double x) {
    return (1.0 / std::sqrt(2.0 * M_PI)) * std::exp(-0.5 * x * x);
}

double ImpliedVolatility::BS_Call_Option_Price(double sigma) {
    double d1 = (std::log(S_0 / K) + (r + 0.5 * sigma * sigma) * tau) / (sigma * std::sqrt(tau));
    double d2 = d1 - sigma * std::sqrt(tau);
    return S_0 * std::erfc(-d1 / std::sqrt(2)) / 2 - K * std::exp(-r * tau) * std::erfc(-d2 / std::sqrt(2)) / 2;
}

double ImpliedVolatility::vega(double sigma) {
    double d1 = (std::log(S_0 / K) + (r + 0.5 * sigma * sigma) * tau) / (sigma * std::sqrt(tau));
    return S_0 * normalPDF(d1) * std::sqrt(tau);
}

double ImpliedVolatility::calculate() {
    const double tolerance = 1e-10;
    int maxIterations = 100;
    int iteration = 0;
    std::ofstream outFile("./csv/implied_volatility_output.csv");

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open output file\n";
        return -1;
    }

    outFile << "Iteration,Sigma,Error\n";
    
    while (iteration < maxIterations) {
        double priceDiff = BS_Call_Option_Price(sigma) - V_market;
        double sigmaVega = vega(sigma);
        
        if (std::abs(priceDiff) < tolerance) break;
        
        sigma -= priceDiff / sigmaVega;
        outFile << iteration + 1 << "," << sigma << "," << priceDiff << "\n";
        iteration++;
    }
    
    outFile.close();
    return sigma;
}
