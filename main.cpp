#include "./utility/DataHandler.h"
#include "./crossOverStrategies/MovingAverageStrategy.h"
#include "./crossOverStrategies/ExponentialMovingAverageStrategy.h"
#include <iostream>

int main() {
    DataHandler dataHandler;

    dataHandler.loadData("./Data/ZOMATO.BSE_stock_data.csv");

    const std::vector<double>& prices = dataHandler.getPrices();
    if (prices.empty()) {
        std::cerr << "No data loaded from the file. Exiting...\n";
        return 1;
    }

    int shortWindow = 9;
    int longWindow = 200;

    ExponentialMovingAverageStrategy strategy(shortWindow, longWindow);

    strategy.execute(prices);

    std::cout << "Strategy output exported to 'strategy_output.csv'\n";

    return 0;
}
