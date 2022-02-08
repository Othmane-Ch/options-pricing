using namespace std;

#include "PricerBlackScholes.h"




PricerBlackScholes::PricerBlackScholes()
{
}



// Standard normal probability density function
double PricerBlackScholes::norm_pdf(const double& x) {
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
}
// Approximation de la fonction de distribution cumulative normale (par des séries de Taylor)

// Fonction reprise du document de Bernt Arne Ødegaard

double PricerBlackScholes::norm_cdf(double z)
{
    double b1 = 0.31938153;
    double b2 = -0.356563782;
    double b3 = 1.781477937;
    double b4 = -1.821255978;
    double b5 = 1.330274429;
    double p = 0.2316419;
    double c2 = 0.3989423;
    double a=fabs(z);
    double t = 1.0/(1.0+a*p);
    double b = c2*exp((-z)*(z/2.0));
    double n = ((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t;
    n = 1.0-b*n;
    if ( z < 0.0 )
        n = 1.0 - n;
    else if (z > 6.0)
        return 1.0;  // éviter les valeurs illicites
    else
        return 0.0;

    return n;
};

// This calculates d_j, for j in {1,2}. This term appears in the closed
// form solution for the European call or put price
double PricerBlackScholes::d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

// Calculate the European vanilla call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double PricerBlackScholes::call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return S * norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double PricerBlackScholes::put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
}



