#include "./utility/DataHandler.h"
#include "./crossOverStrategies/MovingAverageStrategy.h"
#include "./crossOverStrategies/ExponentialMovingAverageStrategy.h"
#include "./crossOverStrategies/RelativeStrengthIndexStrategy.h"
#include "./crossOverStrategies/BollingerBandStrategy.h"
#include "./derivatives/options/ImpliedVolatility.h"
#include <iostream>

int main() {
    DataHandler dataHandler;

    dataHandler.loadData("./Data/GS_stock_data.csv");

    const std::vector<double>& prices = dataHandler.getPrices();
    if (prices.empty()) {
        std::cerr << "No data loaded from the file. Exiting...\n";
        return 1;
    }

    double V_market = 2;
    double K = 120;
    double tau = 1;
    double r = 0.05;
    double S_0 = 100;
    double sigma = 0.25;

    ImpliedVolatility sigmaObj(V_market, K, tau, r, S_0, sigma);
    sigmaObj.calculate();
    std::cout << "Strategy output exported to 'implied_volatility_output.csv'\n";

    return 0;
}
