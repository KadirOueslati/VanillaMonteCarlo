#ifndef CORRELATEDBS_H
#define CORRELATEDBS_H

#include "BlackScholes.h"
#include "ModelConfig.h"
#include "Random.h"

/*
This class inherits from BlackScholes.
We add the member variable m_corr which is the correlation between two correlated brownian motions.
If (B1,B2) are two independent brownian motions, then (W1,W2) defined as:
W1 = B1
W2 = m_corr*W1 + sqrt(1 - m_corr²)* B2
are correlated brownian motion such as <W1,W2> = m_corr
*/

class CorrelatedBS : public BlackScholes
{
    private:
        double m_corr{0};
    public:
        CorrelatedBS(ModelConfig myConf)
            :BlackScholes(myConf),m_corr{myConf.corr}
        {
            m_finalValue                = new double[2];    // We will store two final values
            m_brownianValue             = new double[2];    // We will store two values for the correlated BM

            double Z1{Random::getNormal(0,1)};
            double Z2{Random::getNormal(0,1)};              // These 2 independant realisations of independant gaussian rv will help us generate the correlated BM

            *m_brownianValue            = std::sqrt(m_T)*Z1;
            *(m_brownianValue + 1)      = m_corr*(*m_brownianValue) + std::sqrt((1-std::pow(m_corr,2))*m_T)*Z2;

            *m_finalValue               = *m_startValue*(std::exp((m_r-std::pow(*m_sigma,2)/2)*m_T + (*m_sigma)*(*m_brownianValue)));
            *(m_finalValue + 1)         = *(m_startValue+1)*(std::exp((m_r-std::pow(*(m_sigma+1),2)/2)*m_T + *(m_sigma+1)*(*(m_brownianValue + 1))));
        }
        CorrelatedBS (const CorrelatedBS& otherB): BlackScholes(otherB) // As we have pointer variables in the class, we implement copy constructor to fulfill the 0/3/5 rule
        {
            m_finalValue                = new double[2];
            m_brownianValue             = new double[2];
            for(int i = 0; i < 2; ++i)
            {
                *(m_brownianValue + i)   = *(otherB.m_brownianValue + i);
                *(m_finalValue + i)      = *(otherB.m_finalValue + i);
            }
        }
        CorrelatedBS& operator=(const CorrelatedBS& otherB)            // As we have pointer variables in the class, we implement overload assignement to fulfill the 0/3/5 rule
        {
            if(this == & otherB)    {return *this;}
            for(int i = 0; i < 2; ++i)
            {
                *(m_brownianValue + i)   = *(otherB.m_brownianValue + i);
                *(m_finalValue + i)      = *(otherB.m_finalValue + i);
            }
            return *this;
        }
        ~CorrelatedBS(){};
        double* generateValue() override;           // This method generates new final values without instancing a new object
        double* getValue()const override;           // Getter for m_finalValue
        double* getBrownianValue()const override;   // Getter for m_brownianValue
};

#endif
