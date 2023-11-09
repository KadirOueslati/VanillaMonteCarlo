#include "CorrelatedBS.h"
#include <cmath>

double* CorrelatedBS::generateValue()
{
    double Z1{Random::getNormal(0,1)};
    double Z2{Random::getNormal(0,1)};

    *m_brownianValue            = std::sqrt(m_T)*Z1;
    *(m_brownianValue + 1)      = m_corr*(*m_brownianValue) + std::sqrt((1-std::pow(m_corr,2))*m_T)*Z2;

    *m_finalValue               = *m_startValue*(std::exp((m_r-std::pow(*m_sigma,2)/2)*m_T + (*m_sigma)*(*m_brownianValue)));
    *(m_finalValue + 1)         = *(m_startValue+1)*(std::exp((m_r-std::pow(*(m_sigma+1),2)/2)*m_T + *(m_sigma+1)*(*(m_brownianValue + 1))));

    return m_finalValue;
}

double* CorrelatedBS::getValue()const
{
    return m_finalValue;
}
double* CorrelatedBS::getBrownianValue()const
{
    return m_brownianValue;
}
