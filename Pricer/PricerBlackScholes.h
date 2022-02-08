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

#ifndef PRICER_PRICER_H
#define PRICER_PRICER_H


class PricerBlackScholes {


    public:
        PricerBlackScholes();

        double norm_pdf(const double& x);
        double norm_cdf(double z);
        double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T);
        double call_price(const double& S, const double& K, const double& r, const double& v, const double& T);
        double put_price(const double& S, const double& K, const double& r, const double& v, const double& T);
};


#endif //PRICER_PRICER_H
