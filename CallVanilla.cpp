
#include "CallVanilla.h"

#include <cmath>

double CallVanilla::deltaValue(double* value, double* startValue)
{
    double delta{0};

    if(*value > m_strike)
    {
        delta   =(*value);
        delta   /=(*startValue);
        delta   = actualisation(delta,m_T,m_r);
    }
    return delta;
}

/*void CallVanilla::valueUpdate()*/

double* CallVanilla::payoffValue(double* value,double* startValue,double* volatility,double* brownianValue)
{
    double* valueVector = new double[6];
    switch(m_varianceReduction)
    {
        case 0:
            {
                *valueVector = (*value>m_strike)?(*value-m_strike):0;
                *valueVector = actualisation(*valueVector,m_T,m_r);

                *(valueVector + 1) = deltaValue(value,startValue);
                *(valueVector + 2) = gammaValue(value,startValue,volatility,*brownianValue);
                *(valueVector + 3) = vegaValue(value,volatility,*brownianValue);
                *(valueVector + 4) = thetaValue(value,volatility,*brownianValue);
                *(valueVector + 5) = rhoValue(value);
                return valueVector;
            }
        case 1:
            {
                *valueVector = (*value>m_strike)?(*value-m_strike):0;
                *valueVector = actualisation(*valueVector,m_T,m_r);
                *valueVector -= actualisation(*value,m_T,m_r);
                *valueVector += *startValue;

                *(valueVector + 1) = deltaValue(value,startValue);
                *(valueVector + 2) = gammaValue(value,startValue,volatility,*brownianValue);
                *(valueVector + 3) = vegaValue(value,volatility,*brownianValue);
                *(valueVector + 4) = thetaValue(value,volatility,*brownianValue);
                *(valueVector + 5) = rhoValue(value);
                return valueVector;
            }
    }
    valueVector = nullptr;
    return valueVector;
}

int CallVanilla::getVarianceReduction()const
{
    return m_varianceReduction;
}

double CallVanilla::gammaValue(double* value, double* startValue,double* volatility,double brownianValue)
{
    double gamma{0};

    if(*value > m_strike)
    {
        gamma   = brownianValue*m_strike;
        gamma   /=(std::pow(*startValue,2)*m_T*(*volatility));
        gamma   = actualisation(gamma,m_T,m_r);
    }
    return gamma;
}

double CallVanilla::vegaValue(double* value, double* volatility,double brownianValue)
{
    double vega{0};
    if(*value > m_strike)
    {
        vega   = (*value);
        vega   *=(brownianValue - (*volatility)*m_T);
        vega   = actualisation(vega,m_T,m_r);
    }
    return vega;
}

double CallVanilla::rhoValue(double* value)
{
    double rho{0};
    if(*value > m_strike)
    {
        rho   = (*value-m_strike)*(-m_T);
        rho   += (m_T*(*value));
        rho   = actualisation(rho,m_T,m_r);
    }
    return rho;
}

double CallVanilla::thetaValue(double* value,double* volatility,double brownianValue)
{
    double theta{0};
    if(*value > m_strike)
    {
        theta   += m_strike*m_r;
        theta   -= ((0.5*std::pow(*volatility,2))*(*value));
        theta   += (brownianValue/std::pow(m_T,2)*(*volatility)*0.5*(*value));
        theta   = actualisation(theta,m_T,m_r);
    }
    return -theta;
}

