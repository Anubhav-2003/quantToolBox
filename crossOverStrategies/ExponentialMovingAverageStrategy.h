#ifndef EXPONENTIAL_MOVING_AVERAGE_STRATEGY_H
#define EXPONENTIAL_MOVING_AVERAGE_STRATEGY_H

#include <vector>

class ExponentialMovingAverageStrategy {
public:
    ExponentialMovingAverageStrategy(int shortW, int longW);

    std::vector<double> calculateExponentialMovingAverage(const std::vector<double>& prices, int window);

    void execute(const std::vector<double>& prices);

private:
    int shortWindow;
    int longWindow;
};

#endif
