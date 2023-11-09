#ifndef MODELCONFIG_H
#define MODELCONFIG_H

struct ModelConfig
{
        int     dimension{1};     // Indicates the number of double we dinamically allocate for volatilities, starting values,...
        double* x{nullptr};       // Pointer of starting value(s) of the underlying(s)
        double* sigma{nullptr};   // Pointer of historical volatility(ies) of the underlying(s)
        double  r{0};             // Money Market Account rate, under risk-neutral probability, equals to the expected return rate of the stock
        double  T{0};             // The time horizon
        double  corr{0};          // Correlation of the two brownian(s) when there are two correlated BM
};

#endif // MODELCONFIG_H
