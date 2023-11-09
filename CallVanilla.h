#ifndef CALLVANILLA_H
#define CALLVANILLA_H

#include "PayoffConfig.h"
#include "ModelConfig.h"
#include "Payoff.h"

class CallVanilla : public Payoff
{
    private:
        int m_varianceReduction{0};
    public:
        CallVanilla(PayoffConfig pConf,ModelConfig mConf,int i)
            :Payoff(pConf,mConf),m_varianceReduction{i}
            {
            }

        double* payoffValue(double* value,double* startValue,double* volatility,double* brownianValue) override;
        double  deltaValue(double* value, double* startValue) override;
        double  gammaValue(double* value, double* startValue,double* volatility,double brownianValue) override;
        double  vegaValue(double* value, double* volatility,double brownianValue) override;
        double  rhoValue(double* value)override;
        double  thetaValue(double* value,double* volatility,double brownianValue)override;
        int     getVarianceReduction()const override;
};

#endif // CALLVANILLA_H
