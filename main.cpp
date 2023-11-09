#include <cassert>
#include <chrono>
#include <iostream>
#include <set>

#include "BestOfCall.h"
#include "BlackScholes.h"
#include "CallVanilla.h"
#include "CorrelatedBS.h"
#include "ModelConfig.h"
#include "Models.h"
#include "MonteCarlo.h"
#include "Payoff.h"
#include "PayoffConfig.h"
#include "PutVanilla.h"
#include "Random.h"
//#include "Timer.h"

struct mainConfig{
        int     dimension{1};     // Indicates the number of double we dinamically allocate for volatilities, starting values,...
        double* x{nullptr};       // Pointer of starting value(s) of the underlying(s)
        double* sigma{nullptr};   // Pointer of historical volatility(ies) of the underlying(s)
        double  r{0};             // Money Market Account rate, under risk-neutral probability, equals to the expected return rate of the stock
        double  T{0};             // The time horizon
        double  corr{0};
        double  strike{0};        // Strike of the derivative
        int     nbInterest{0};    // Number of values we compute with the MC simulation (Price and sensibiliti
        int     nbUnderlying{0};
};

void ConfigSetting(const int userChoice, mainConfig& mainConf)
{
    switch(userChoice)
    {
        case 1 : {
                    std::cout << "Please enter the spot value of the underlying :\n";
                    mainConf.x = new double[1];
                    std::cin >> *mainConf.x;
                    std::cout << "Please enter the volatility of the underlying (0.2 for 20%) :\n";
                    mainConf.sigma = new double[1];
                    std::cin >> *mainConf.sigma;
                    std::cout << "Please enter the risk-free rate (0.05 for 5%) :\n";
                    std::cin >> mainConf.r;
                    std::cout << "Please enter the maturity in days :\n";
                    std::cin >> mainConf.T;
                    mainConf.T /= 365;
                    std::cout << "Please enter the strike of the option :\n";
                    std::cin >> mainConf.strike;
                    mainConf.nbInterest = 6;
                    mainConf.nbUnderlying = 1;
                    break;
        }
        case 2 : {
                    std::cout << "Please enter the spot value of the underlying :\n";
                    mainConf.x = new double[1];
                    std::cin >> *mainConf.x;
                    std::cout << "Please enter the volatility of the underlying (0.2 for 20%) :\n";
                    mainConf.sigma = new double[1];
                    std::cin >> *mainConf.sigma;
                    std::cout << "Please enter the risk-free rate (0.05 for 5%) :\n";
                    std::cin >> mainConf.r;
                    std::cout << "Please enter the maturity in days :\n";
                    std::cin >> mainConf.T;
                    mainConf.T /= 365;
                    std::cout << "Please enter the strike of the option :\n";
                    std::cin >> mainConf.strike;
                    mainConf.nbInterest = 6;
                    mainConf.nbUnderlying = 1;
                    break;
        }
        case 3 : {
                    std::cout << "Please enter the spot value of the first underlying :\n";
                    mainConf.x = new double[2];
                    std::cin >> *mainConf.x;
                    std::cout << "Please enter the spot value of the second underlying :\n";
                    std::cin >> *(mainConf.x +1);
                    std::cout << "Please enter the volatility of the first underlying (0.2 for 20%) :\n";
                    mainConf.sigma = new double[2];
                    std::cin >> *mainConf.sigma;
                    std::cout << "Please enter the volatility of the second underlying (0.2 for 20%) :\n";
                    std::cin >> *(mainConf.sigma +1);
                    std::cout << "Please enter the risk-free rate (0.05 for 5%) :\n";
                    std::cin >> mainConf.r;
                    std::cout << "Please enter the maturity in days :\n";
                    std::cin >> mainConf.T;
                    mainConf.T /= 365;
                    std::cout << "Please enter the strike of the option :\n";
                    std::cin >> mainConf.strike;
                    std::cout << "Please enter the correlation between the two underlyings (0 to 1) :\n";
                    std::cin >> mainConf.corr;
                    mainConf.nbInterest = 1;
                    mainConf.nbUnderlying = 2;
                    break;
        }
    }
}

void MonteCarloLauncher(const int userChoice, const mainConfig mainConf)
{
    using namespace std::chrono;

    switch(userChoice)
    {
        case 1 : {
                    ModelConfig mConf{mainConf.nbUnderlying,mainConf.x,mainConf.sigma,mainConf.r,mainConf.T,mainConf.corr};

                    PayoffConfig pConf{mainConf.T,mainConf.strike,mainConf.nbInterest,mainConf.nbUnderlying};
                    BlackScholes myBS(mConf);

                    int varianceReduction{0};

                    CallVanilla myPayoff(pConf,mConf,varianceReduction);

                    std::cout << "Please enter the number of simulations :\n";
                    long numberOfSimulations{};
                    std::cin >> numberOfSimulations;
                    const auto t1 = high_resolution_clock::now();
                    MonteCarlo Sim(pConf,mConf,myBS,myPayoff,numberOfSimulations);
                    const auto t2 = high_resolution_clock::now();
                    const auto timeElapsed = duration_cast<milliseconds>(t2-t1).count();
                    std::cout << "Time of the MonteCarlo process : " << timeElapsed << " ms" << '\n';
                    Sim.resultMC();
                    break;
        }
        case 2 : {
                    ModelConfig mConf{mainConf.nbUnderlying,mainConf.x,mainConf.sigma,mainConf.r,mainConf.T,mainConf.corr};

                    PayoffConfig pConf{mainConf.T,mainConf.strike,mainConf.nbInterest,mainConf.nbUnderlying};
                    BlackScholes myBS(mConf);

                    // We instantiate the payoff
                    int varianceReduction{0};       //  Crude Monte Carlo choose 0
                    //  Variance reduction Monte Carlo choose 1
                    PutVanilla myPayoff(pConf,mConf,varianceReduction);

                    // We proceed to the evaluation using MonteCarlo
                    std::cout << "Please enter the number of simulations :\n";
                    long numberOfSimulations{};
                    std::cin >> numberOfSimulations;
                    const auto t1 = high_resolution_clock::now();
                    MonteCarlo Sim(pConf,mConf,myBS,myPayoff,numberOfSimulations);
                    const auto t2 = high_resolution_clock::now();
                    const auto timeElapsed = duration_cast<milliseconds>(t2-t1).count();
                    std::cout << "Time of the MonteCarlo process : " << timeElapsed << " ms" << '\n';
                    Sim.resultMC();
                    break;
        }
        case 3 : {
                    ModelConfig mConf{mainConf.nbUnderlying,mainConf.x,mainConf.sigma,mainConf.r,mainConf.T,mainConf.corr};

                    PayoffConfig pConf{mainConf.T,mainConf.strike,mainConf.nbInterest,mainConf.nbUnderlying};
                    CorrelatedBS myBS(mConf);

                    // We instantiate the payoff
                    int varianceReduction{0};       //  Crude Monte Carlo choose 0
                    //  Variance reduction Monte Carlo choose 1
                    BestOfCall myPayoff(pConf,mConf,varianceReduction);

                    // We proceed to the evaluation using MonteCarlo
                    std::cout << "Please enter the number of simulations :\n";
                    long numberOfSimulations{};
                    std::cin >> numberOfSimulations;
                    auto t1 = high_resolution_clock::now();
                    MonteCarlo Sim(pConf,mConf,myBS,myPayoff,numberOfSimulations);
                    auto t2 = high_resolution_clock::now();
                    const auto timeElapsed = duration_cast<milliseconds>(t2-t1).count();
                    std::cout << "Time of the MonteCarlo process : " << timeElapsed << " ms" << '\n';
                    Sim.resultMC();
                    break;
        }
    }
}

void optionChoice(int& myChoice)
{
    while(myChoice < 1 || myChoice > 3)
    {
        std::cin >> myChoice;
        if(myChoice < 1 || myChoice > 3)
        {
            std::cerr << "Please enter a number given above.\n";
        }
    }
}

int main()
{
    std::array<std::string,3> listOfModels {"European Call","European Put","Best-of Call"};

    mainConfig mainConf{};
    std::cout << "What type of option do you want to price using Monte Carlo simulations (chose one of the number below) : \n";
    for (const auto& names : listOfModels)
    {
        static int index{1};
        std::cout << index << ") " << names << '\n';
        ++ index;
    }

    int userChoice{0};
    optionChoice(userChoice);

    ConfigSetting(userChoice,mainConf);
    MonteCarloLauncher(userChoice,mainConf);

    return 0;
}
