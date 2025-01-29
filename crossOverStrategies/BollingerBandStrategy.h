#ifndef BOLLINGER_BAND_STRATEGY_H
#define BOLLINGER_BAND_STRATEGY_H

#include <vector>

class BollingerBandStrategy {
public:
    BollingerBandStrategy(int period, double stdDevFactor);
    void execute(const std::vector<double>& prices);

private:
    int period;
    double stdDevFactor;
    std::vector<double> calculateMovingAverage(const std::vector<double>& prices, int window);
    std::vector<double> calculateStandardDeviation(const std::vector<double>& prices, const std::vector<double>& movingAverage, int window);
};

#endif
