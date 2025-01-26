#ifndef RELATIVE_STRENGTH_INDEX_STRATEGY_H
#define RELATIVE_STRENGTH_INDEX_STRATEGY_H

#include <vector>

class RelativeStrengthIndexStrategy {
public:
    RelativeStrengthIndexStrategy(int rsiPeriod, double overboughtThreshold, double oversoldThreshold);

    void execute(const std::vector<double>& prices);

private:
    int period;          
    double overbought;          
    double oversold;   

    std::vector<double> calculateRSI(const std::vector<double>& prices, int period);
};

#endif
