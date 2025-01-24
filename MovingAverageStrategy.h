#ifndef MOVINGAVERAGESTRATEGY_H
#define MOVINGAVERAGESTRATEGY_H

#include <vector>

class MovingAverageStrategy {
private:
    int shortWindow;
    int longWindow;

    std::vector<double> calculateMovingAverage(const std::vector<double>& prices, int window);

public:
    MovingAverageStrategy(int shortW, int longW);
    void execute(const std::vector<double>& prices);
};

#endif
