#include "BlackScholes.h"

double* BlackScholes::generateValue()
{
    *m_brownianValue = std::sqrt(m_T)*Random::getNormal(0,1);
    double A {(m_r-std::pow(*m_sigma,2)/2)*m_T};
    double B {*m_sigma*(*m_brownianValue)};
    *m_finalValue = (std::exp(A+B))*(*m_startValue);
    return m_finalValue;
}

double* BlackScholes::getValue()const
{
    return m_finalValue;
}
double* BlackScholes::getBrownianValue()const
{
    return m_brownianValue;
}

