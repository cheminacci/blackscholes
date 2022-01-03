// blackscholes.cpp

#include "blackscholes.h"

using std::numbers::pi;

double sigma(Option& opt)
{	return scinge::standard_deviation(opt.spot_price); }

double normal_cdf(const double& x)
{
	double k = 1.0 / (1.0 + 0.2316419 * x);
    double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) 
	{	return ( 1.0 - (1.0 / (pow(2 * pi, 0.5) ) ) * exp(-0.5 * x * x) * k_sum) ;}
	else 
	{	return 1.0 - normal_cdf(-1 * x); }
}

double normal_pdf(double& x)
{	return pow((pi * 2), -0.5) * exp(-0.5 * x * x) ; }

double call_option_price(Option& opt)
{
	double d1, d2;

	d1 = (log(opt.spot_price[0]/opt.strike_price) + (opt.interest_rate + pow(sigma(opt),2)/2 ) * opt.time_to_maturity) / ( sigma(opt) * sqrt(opt.time_to_maturity) ) ;
	d2 = d1 - ( sigma(opt) * sqrt(opt.time_to_maturity) ) ;

	return (normal_cdf(d1) * opt.spot_price[0]) - (opt.strike_price * exp(-1 * opt.interest_rate * opt.time_to_maturity) * normal_cdf(d2)) ;
}

