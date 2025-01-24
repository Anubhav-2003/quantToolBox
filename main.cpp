#include "DataHandler.h"
#include "MovingAverageStrategy.h"
#include <iostream>

int main() {
    DataHandler dataHandler;

    dataHandler.loadData("./Data/GS_stock_data.csv");

    const std::vector<double>& prices = dataHandler.getPrices();
    if (prices.empty()) {
        std::cerr << "No data loaded from the file. Exiting...\n";
        return 1;
    }

    int shortWindow = 5;
    int longWindow = 10;

    MovingAverageStrategy strategy(shortWindow, longWindow);

    strategy.execute(prices);

    std::cout << "Strategy output exported to 'strategy_output.csv'\n";

    return 0;
}
