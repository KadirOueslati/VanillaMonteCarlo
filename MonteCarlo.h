#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "ModelConfig.h"
#include "PayoffConfig.h"
#include "Models.h"
#include "Payoff.h"

#include <cmath>
#include <iomanip>

// Return the lower bound of a 95% Confidence Interval given expectation estimator(a), variance estimator(b) and size of sample(n)
double lowerIC(double a, double b, int n)
{
    return a - 1.96*b/std::sqrt(n);
}

// Return the upper bound of a 95% Confidence Interval given expectation estimator(a), variance estimator(b) and size of sample(n)
double upperIC(double a, double b, int n)
{
    return a + 1.96*b/std::sqrt(n);
}

// Addition pointwise of two dynamic double vectors
template <typename T>
void addPtr(T* A,T* P,int M)
{
    for(int i = 0;i < M;++i)
    {
        *(A+i) += *(P+i);
    }
}

/* This class is based on the mother classes Models and Payoffs*/
class MonteCarlo
{
    private:
        int      m_nbSimulations{0};
        double*  m_valVector{nullptr};
        double   m_expectationHat{0};
        double   m_varianceHat{0};
        double   m_delta{0};
        double   m_gamma{0};
        double   m_rho{0};
        double   m_vega{0};
        double   m_theta{0};
        double   m_lowerBound{0};
        double   m_upperBound{0};
    public:
        MonteCarlo(PayoffConfig pConfig,ModelConfig mConfig,Model& myM, Payoff& myP, int nbSimulations)
                :m_nbSimulations{nbSimulations}
        {
            m_valVector = new double[pConfig.nbInterest];
            double*  modelVal{nullptr};
            double*  brownianVal{nullptr};
            double*  payoffVal{nullptr};

            modelVal            = myM.generateValue();
            brownianVal         = myM.getBrownianValue();

            m_valVector    = myP.payoffValue(modelVal,mConfig.x,mConfig.sigma,brownianVal);
            for(int k = 2; k < m_nbSimulations + 1; ++k)
            {
                modelVal            = myM.generateValue();
                brownianVal         = myM.getBrownianValue();
                /* We generate a new geometric brownian final value to evaluate the payoff and the sensibilities */

                payoffVal           = myP.payoffValue(modelVal,mConfig.x,mConfig.sigma,brownianVal);
                /* Evaluation of the Payoff */

                m_varianceHat       *= (k-2);
                m_varianceHat       /= (k-1);
                m_varianceHat       += std::pow((*payoffVal-m_expectationHat),2);
                m_varianceHat       /= k;

                addPtr<double>(m_valVector,myP.payoffValue(modelVal,mConfig.x,mConfig.sigma,brownianVal),pConfig.nbInterest);
            }
            m_expectationHat    = ((*m_valVector)/m_nbSimulations);
            m_delta             = (*(m_valVector+1)/m_nbSimulations);
            m_gamma             = (*(m_valVector+2)/m_nbSimulations);
            m_vega              = (*(m_valVector+3)/m_nbSimulations);
            m_theta             = (*(m_valVector+4)/m_nbSimulations);
            m_rho               = (*(m_valVector+5)/m_nbSimulations);

            m_lowerBound        = lowerIC(m_expectationHat,m_varianceHat,m_nbSimulations);
            m_upperBound        = upperIC(m_expectationHat,m_varianceHat,m_nbSimulations);
        }

        void resultMC() const
        {
            std::cout << std::setprecision(4);
            std::cout << "Final value : " << m_expectationHat <<'\n';
            std::cout << std::setprecision(6);
            std::cout << "Confidence Interval at 95% : [ " << m_lowerBound << ';' << m_upperBound << " ]" <<'\n';
            std::cout << std::setprecision(3);
            if(m_delta != 0)
            {
            std::cout << "Delta value  : " << m_delta  << '\n';
            std::cout << "Gamma value  : " << m_gamma  << '\n';
            std::cout << "Vega  value  : " << m_vega/100   << '\n';
            std::cout << "Rho   value  : " << m_rho/100    << '\n';
            std::cout << "Theta value  : " << m_theta/365  << '\n';
            }
        }

};
#endif // MONTECARLO_H*/

