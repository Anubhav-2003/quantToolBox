#ifndef IMPLIED_VOLATILITY_H
#define IMPLIED_VOLATILITY_H

#include <cmath>

class ImpliedVolatility {
public:
    ImpliedVolatility(double marketPrice, double strike, double timeToMaturity, double riskFreeRate, double spotPrice, double initialGuess);
    double calculate();

private:
    double V_market;
    double K;
    double tau;
    double r;
    double S_0;
    double sigma;
    
    double normalPDF(double x);
    double BS_Call_Option_Price(double sigma);
    double vega(double sigma);
};

#endif
