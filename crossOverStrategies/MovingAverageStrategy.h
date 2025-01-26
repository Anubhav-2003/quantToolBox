#ifndef MOVING_AVERAGE_STRATEGY_H
#define MOVING_AVERAGE_STRATEGY_H

#include <vector>

class MovingAverageStrategy {
public:
    MovingAverageStrategy(int shortW, int longW);
    void execute(const std::vector<double>& prices);
private:
    int shortWindow;
    int longWindow;

    std::vector<double> calculateMovingAverage(const std::vector<double>& prices, int window);
};

#endif
