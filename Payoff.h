#ifndef PAYOFF_H
#define PAYOFF_H

#include <cmath>
#include "PayoffConfig.h"
#include "ModelConfig.h"

double actualisation(double value, double time, double rate); // Function to change the numeraire

/*
Payoff header contains the payoff' classes definition.
Payoff class is a pure abstract class that contains the common features of the payoffs (Call Vanilla, Put Vanilla, Best-of Call,...)
We could have used lambdas to represent the payoffs but a class eases the computation of the sensibilities and avoids rewriting.
*/

class Payoff
{
    protected:
        double m_strike{0};
        double m_T{0};
        int    m_nb{0};     // Defines how many variables will be computed : the payoff value + the number of sensibilities
        double m_r{0};
    public:
        Payoff(PayoffConfig pConf,ModelConfig mConf)
            :m_strike{pConf.strike},m_T{pConf.T},m_nb{pConf.nbInterest},m_r{mConf.r}
            {
            }
        virtual ~Payoff(){};
        virtual double* payoffValue(double *,double*,double*,double*)=0;
        virtual double deltaValue(double *,double*)=0;
        virtual double gammaValue(double *,double*,double*,double)=0;
        virtual double vegaValue(double *,double*,double)=0;
        virtual double rhoValue(double*)=0;
        virtual double thetaValue(double*,double*,double)=0;
        virtual int getVarianceReduction()const=0;
};

#endif
