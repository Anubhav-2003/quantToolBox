#include "./utility/DataHandler.h"
#include "./crossOverStrategies/MovingAverageStrategy.h"
#include "./crossOverStrategies/ExponentialMovingAverageStrategy.h"
#include "./crossOverStrategies/RelativeStrengthIndexStrategy.h"
#include "./crossOverStrategies/BollingerBandStrategy.h"
#include <iostream>

int main() {
    DataHandler dataHandler;

    dataHandler.loadData("./Data/GS_stock_data.csv");

    const std::vector<double>& prices = dataHandler.getPrices();
    if (prices.empty()) {
        std::cerr << "No data loaded from the file. Exiting...\n";
        return 1;
    }

    int shortWindow = 9;
    int longWindow = 200;
    int period = 13;
    int overbought = 60;
    int oversold = 40;
    int stdDevFactor = 2;
    BollingerBandStrategy strategy(period, stdDevFactor);

    strategy.execute(prices);

    std::cout << "Strategy output exported to 'strategy_output.csv'\n";

    return 0;
}
