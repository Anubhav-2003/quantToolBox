#include "DataHandler.h"
#include "MovingAverageStrategy.h"
#include <iostream>

int main() {
    DataHandler dataHandler;
    dataHandler.loadData("historical_prices.csv");

    const auto& prices = dataHandler.getPrices();
    if (prices.empty()) {
        std::cerr << "No data loaded. Exiting...\n";
        return 1;
    }

    int shortWindow = 5;
    int longWindow = 20;
    MovingAverageStrategy strategy(shortWindow, longWindow);

    strategy.execute(prices);

    return 0;
}
