using namespace std;
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "PricerBlackScholes.h"
#include "PricerMonteCarlo.h"


#include <string>


int main() {

    PricerBlackScholes BS;


    //  double S = atof(argv[0]);  // Spot Price
    //  double K = atof(argv[1]);  // Strike Price
    //  double T = atof(argv[2]);      // Maturity in Years
    //  double r = atof(argv[3]);  // Interest Rate
    //  double q = atof(argv[4]);     // Dividend yeild
    //  double v = atof(argv[5]);   // Volatility


    srand (time (0));  // Set the seed for random number generation
    double S = 100.0;  // Spot Price
    double K = 100.0;  // Strike Price
    double T = 1;      // Maturity in Years
    double r = 0.05;  // Interest Rate
    double q = 0;     // Dividend yeild
    double v = 0.2;   // Volatility


    // les valeurs par black Scholes
    double BSCall = BS.call_price (S, K, r, v, T);
    double BSPut = BS.put_price(S, K, r, v, T);

    PricerMonteCarlo MC;

    int Nsims = 1e7;  // Number of simulations // on peut à chaque fois modifier et voir le résultat
    double Z;   // Random standard normal Z(0,1)
    vector < double >ST (Nsims, 0.0); // Initialize terminal prices S(T)
    vector < double >ST_K (Nsims, 0.0); // Initialize call payoff
    vector < double >K_ST (Nsims, 0.0); // Initialize put payoff
    double u1, u2;
    double pi = 3.141592653589793;
    for (int i = 0; i <= Nsims - 1; i++)
    {
// Independent uniform random variables
        u1 = ((double) rand () / ((double) (RAND_MAX) + (double) (1)));
        u2 = ((double) rand () / ((double) (RAND_MAX) + (double) (1)));
// Floor u1 to avoid errors with log function
        u1 = max (u1, 1.0e-10);
// Z ~ N(0,1) by Box-Muller transformation
        Z = sqrt (-2.0 * log (u1)) * sin (2 * pi * u2);
        ST[i] = S * exp ((r - q - 0.5 * v * v) * T + v * sqrt (T) * Z); // Simulated terminal price S(T)
        ST_K[i] = max (ST[i] - K, 0.0); // Call payoff
        K_ST[i] = max (K - ST[i], 0.0); // Put payoff
    }
// Simulated prices as discounted average of terminal prices
    double BSCallSim = exp (-r * T) * MC.VecMean (ST_K);  // les valeurs de la simulation de Monte Carlo
    double BSPutSim = exp (-r * T) * MC.VecMean (K_ST);


// Errors
    double CallError = BSCall - BSCallSim;
    double PutError = BSPut - BSPutSim;

    // Then we calculate the call/put values
    double call = BS.call_price(S, K, r, v, T);
    double put = BS.put_price(S, K, r, v, T);

    // Finally we output the parameters and prices
    cout << "Underlying:      " << S << std::endl;
    cout << "Strike:          " << K << std::endl;
    cout << "Risk-Free Rate:  " << r << std::endl;
    cout << "Volatility:      " << v << std::endl;
    cout << "Maturity:        " << T << std::endl;
    cout << "Call Price:      " << call << std::endl;
    cout << "Put Price:       " << put << std::endl;

// Output the results
    cout << setprecision (4) << fixed;
    cout << "Using " << Nsims << " simulations..." << endl;
    cout << " " << endl;
    cout << "Method CallPrice PutPrice " << endl;
    cout << "----------------------------------" << endl;
    cout << "Simulation " << BSCallSim << " " << BSPutSim << endl;
    cout << "Closed Form " << BSCall << " " << BSPut << endl;
    cout << "Error " << CallError << " " << PutError << endl;
    cout << "----------------------------------" << endl;
    cout << " " << endl;
    system ("PAUSE");
}

