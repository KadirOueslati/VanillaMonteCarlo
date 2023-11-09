#include "Payoff.h"

double actualisation(double value, double time, double rate)
{
    return value*std::exp(-time*rate);
}
