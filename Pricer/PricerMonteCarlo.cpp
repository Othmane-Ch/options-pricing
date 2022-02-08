#include <vector>
using namespace std;

#include "PricerMonteCarlo.h"






PricerMonteCarlo::PricerMonteCarlo()
{
}

double PricerMonteCarlo::VecMean (vector <double> x)
{
    int n = x.size ();
    double sum = 0.0;
    for (int i = 0; i <= n - 1; i++)
        sum += x[i];
    double xbar = sum / n;
    return xbar;
}