#ifndef PAYOFFCONFIG_H
#define PAYOFFCONFIG_H

struct PayoffConfig
{
    double  T{0};             // Maturity of the payoff
    double  strike{0};        // Strike of the derivative
    int     nbInterest{0};    // Number of values we compute with the MC simulation (Price and sensibiliti
    int     nbUnderlying{0};  // Number of underlyings
};

#endif
