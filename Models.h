#ifndef MODELS_H
#define MODELS_H

#include "ModelConfig.h"
#include "Random.h"
#include <iostream>
#include <cmath>

/*
Models header contains the models' classes definition.
Model class is a pure abstract class that contains the common features of the models of interest (BlackScholes, Ornstein-Uhlenbeck,...)
The other models inherit from Model class and generate values given parameters given by the Config structs
*/

/*
This class will generate values for diffusions S(t)) represented by the homogeneous SDE:
dS(t) = m_r*dt + m_sigma*dW(t)
where W(t) is a standard brownian motion.
As m_r and m_sigma are constants, the SDE has a unique solution and we assume that we can resolve the SDE.
We do not use Euler or Milstien Schemes for such diffusions.
*/

class Model
{
    protected:
        double*  m_sigma{nullptr};
        double   m_r{};
        double   m_T{};
        double*  m_startValue{nullptr};
        int      m_nbBM{0};             // Number of dimension (to manage correlated paths)
    public:
        Model(ModelConfig myConf):m_r{myConf.r},m_T{myConf.T},m_nbBM{myConf.dimension}
        {
            m_sigma         = new double[m_nbBM];
            for(int i = 0;i < m_nbBM; ++i)                  // We perform deep copies from the config structs to prevent undefined behaviour
            {
                *(m_sigma + i) = *(myConf.sigma + i);
            }
            m_startValue    = new double[m_nbBM];
            for(int i = 0;i < m_nbBM; ++i)
            {
                *(m_startValue + i) = *(myConf.x + i);
            }
        }
        Model(const Model& otherM) // As we have pointer variables in the class, we implement copy constructor to fulfill the 0/3/5 rule
        {
            m_r     = otherM.m_r;
            m_T     = otherM.m_T;
            m_nbBM  = otherM.m_nbBM;
            m_sigma = new double[m_nbBM];
            for(int i = 0;i < m_nbBM; ++i)
            {
                *(m_sigma + i) = *(otherM.m_sigma + i);
            }
            m_startValue    = new double[m_nbBM];
            for(int i = 0;i < m_nbBM; ++i)
            {
                *(m_startValue + i) = *(otherM.m_startValue + i);
            }
        }
        Model& operator=(const Model& otherM)  // As we have pointer variables in the class, we implement overload assignement to fulfill the 0/3/5 rule
        {
            if(this == &otherM) {return *this;}
            m_r     = otherM.m_r;
            m_T     = otherM.m_T;
            m_nbBM  = otherM.m_nbBM;
            m_sigma = new double[m_nbBM];
            for(int i = 0;i < m_nbBM; ++i)
            {
                *(m_sigma + i) = *(otherM.m_sigma + i);
            }
            m_startValue    = new double[m_nbBM];
            for(int i = 0;i < m_nbBM; ++i)
            {
                *(m_startValue + i) = *(otherM.m_startValue + i);
            }
            return *this;
        }
        virtual ~ Model(){delete m_startValue;delete m_sigma;}
        virtual double*  getValue()const=0 ;            // Getter of the value of the model
        virtual double*  generateValue() =0;            // This method generates value without instancing an other object
        virtual double*  getBrownianValue() const=0 ;   // Getter of the value of the brownian motion
};

#endif // MODELS_H
