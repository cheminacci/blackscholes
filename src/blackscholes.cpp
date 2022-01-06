// blackscholes.cpp

#include "blackscholes.hpp"

using std::numbers::pi;

constexpr double sigma(Option& opt)
{	return scinge::standard_deviation(opt.spot_price); }

constexpr double sigma_percent(Option& opt)
{	return (scinge::standard_deviation(opt.spot_price)) / scinge::average(opt.spot_price); }

constexpr double normal_cdf(const double& x)
{
	double k = 1.0 / (1.0 + 0.2316419 * x);
    double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) 
	{	return ( 1.0 - (1.0 / (pow(2 * pi, 0.5) ) ) * exp(-0.5 * x * x) * k_sum) ;}
	else 
	{	return 1.0 - normal_cdf(-x); }
}

constexpr double my_normal_cdf(const double& x, const double& mean, const double& sigma)
{	return ( 1.0 / (sigma * sqrt(2*pi)) ) * -exp( -0.5 * pow(((x - mean) / sigma) , 2) ) ;}

constexpr double normal_pdf(double& x)
{	return pow((pi * 2), -0.5) * exp(-0.5 * x * x) ; }

constexpr double call_option_price(Option& opt)
{
	double d1, d2;

	d1 = (log(opt.spot_price[0]/opt.strike_price) + (opt.interest_rate + pow(sigma_percent(opt),2)/2 ) * opt.time_to_maturity) / ( sigma_percent(opt) * sqrt(opt.time_to_maturity) ) ;
	d2 = d1 - ( sigma_percent(opt) * sqrt(opt.time_to_maturity) ) ;

	return (my_normal_cdf(d1, scinge::average(opt.spot_price), sigma_percent(opt)) * opt.spot_price[0]) - (opt.strike_price * exp(-opt.interest_rate * opt.time_to_maturity) * my_normal_cdf(d2, scinge::average(opt.spot_price), sigma_percent(opt))) ;
}

constexpr double put_option_price(Option& opt)
{	return ( opt.strike_price * exp(-opt.interest_rate * opt.time_to_maturity) ) - opt.spot_price[0] + call_option_price(opt) ;}