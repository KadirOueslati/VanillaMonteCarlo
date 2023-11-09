#include "BestOfCall.h"
#include <cmath>

double* BestOfCall::payoffValue(double* value,double* startValue,double* volatility,double* brownianValue)
{
    double* payoffValue = new double[1];
    *payoffValue        = 0;
    double maxValue{std::max(*value,*(value + 1))};
    if(maxValue > m_strike)
    {
        *payoffValue = (maxValue - m_strike);
        *payoffValue = actualisation(*payoffValue,m_T,m_r);
        return payoffValue;
    }
    return payoffValue;
}

double BestOfCall::deltaValue(double* value, double* startValue)
{
    double delta{0};
    return delta;
}

int BestOfCall::getVarianceReduction()const
{
    return m_varianceReduction;
}

double BestOfCall::gammaValue(double* value, double* startValue,double* volatility,double brownianValue)
{
    double gamma{0};
    return gamma;
}

double BestOfCall::vegaValue(double* value, double* volatility,double brownianValue)
{
    double vega{0};
    return vega;
}

double BestOfCall::rhoValue(double* value)
{
    double rho{0};
    return rho;
}

double BestOfCall::thetaValue(double* value,double* volatility,double brownianValue)
{
    double theta{0};
    return theta;
}

