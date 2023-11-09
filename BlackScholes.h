#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

#include "Models.h"
#include "ModelConfig.h"
#include "Random.h"
#include <cmath>

/*
This class inherits from Models.
We add member variables we need to price derivates and compute sensibilities such as the brownian motion value
and the value of the diffusion at time T.
*/
class BlackScholes : public Model
{
    protected:
        double* m_brownianValue{nullptr};
        double* m_finalValue{nullptr};
    public:
        BlackScholes(ModelConfig mConf)
            :Model(mConf)
        {
            m_brownianValue  = new double[1];
            *m_brownianValue = std::sqrt(m_T)*Random::getNormal(0,1);

            double A {(m_r-std::pow(*m_sigma,2)/2)*m_T};
            double B {*m_sigma*(*m_brownianValue)};
            m_finalValue = new double[1];
            *m_finalValue = (std::exp(A+B))*(*m_startValue);
        }
        BlackScholes (const BlackScholes& otherB): Model(otherB) // As we have pointer variables in the class, we implement copy constructor to fulfill the 0/3/5 rule
        {
            m_brownianValue  = new double[1];
            *m_brownianValue = *otherB.m_brownianValue;
            m_finalValue = new double[1];
            *m_finalValue = *otherB.m_finalValue;
        }
        BlackScholes& operator=(const BlackScholes& otherB)  // As we have pointer variables in the class, we implement overload assignement to fulfill the 0/3/5 rule
        {
            if(this == &otherB) {return *this;}
            *m_brownianValue = *otherB.m_brownianValue;
            *m_finalValue = *otherB.m_finalValue;
            return *this;
        }
        ~BlackScholes(){delete m_finalValue;delete m_brownianValue;};
        double* generateValue() override;
        double* getValue()const override;
        double* getBrownianValue()const override;
};

#endif // BLACKSCHOLES_H
