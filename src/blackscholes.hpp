// blackscholes.hpp

#pragma once

#include "scinge.hpp"
#include <cmath>
#include <numbers>
#include <array>

struct Option
{
	std::array<double, 15> spot;	// S(t)
	double strike;	// K	
	double interest;	// r
	double time;	// T or (T - t)
};

using std::numbers::pi;

constexpr double sigma(const Option& opt)
{	
	return scinge::standard_deviation(opt.spot); 
}

constexpr double sigma_percent(const Option& opt)
{	
	return scinge::standard_deviation(opt.spot) / scinge::average(opt.spot); 
}

constexpr double discount_factor(const Option& opt)	// D(r,T)
{
	return std::exp(-1 * opt.interest * opt.time);
}

constexpr double normal_cdf_other(const double& x) // N(x)
{
	const double k = 1.0 / (1.0 + 0.2316419 * x);
    const double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) 
	{	return ( 1.0 - (pow(2 * pi, -0.5)) * exp(-0.5 * x * x) * k_sum ) ;}
	else 
	{	return (1.0 - normal_cdf_other(-x)); }
}

constexpr double my_normal_distribution(const double& x, const double& mean, const double& sigma)
{	
	double C = ( 1.0 / (sigma * pow((2*pi), 0.5)) );
	double X =  -0.5 * ((x - mean ) / sigma) * ((x - mean ) / sigma); 

	return  C * exp(X) ;
}

constexpr double normal_cdf(const double& x) // N(x)
{
    return std::erfc(-x/std::sqrt(2))/2;
}

constexpr double normal_pdf(const double& x) // N'(x)
{	
	return ( (std::pow((pi * 2), -0.5)) * std::exp(-0.5 * x * x) ); 
}

constexpr double d1(const Option& opt)
{
	const double sig_p = sigma_percent(opt);
	
	return ( std::log(opt.spot[0]/opt.strike) + ((opt.interest + (std::pow(sig_p,2)/2)) * opt.time) ) / ( sig_p * std::sqrt(opt.time) );
}

constexpr double d2(const Option& opt)
{
	return d1(opt) - (sigma_percent(opt) * std::sqrt(opt.time)) ;
}

constexpr double call_option_price(const Option& opt)	// C(S,t)
{
	return  ( normal_cdf(d1(opt)) * opt.spot[0] ) - ( opt.strike * std::exp(-1 * opt.interest * opt.time) * normal_cdf(d2(opt)) ) ;
}

constexpr double put_option_price(const Option& opt)	// P(S,t)
{
		return ( opt.strike * std::exp(-1 * opt.interest * opt.time) ) - opt.spot[0] + call_option_price(opt) ;
}

constexpr double call_delta(const Option& opt)
{	
	return normal_cdf(d1(opt));
}

constexpr double put_delta(const Option& opt)
{	
	return normal_cdf(d1(opt)) - 1;
}

constexpr double gamma(const Option& opt)
{
	return normal_pdf(d1(opt)) / (opt.spot[0] * sigma_percent(opt) * std::sqrt(opt.time));	
}

constexpr double vega(const Option& opt)
{	
	return opt.spot[0] * normal_pdf(d1(opt)) * std::sqrt(opt.time);	
}

constexpr double call_theta(const Option& opt)
{	
	return 	( (opt.spot[0] * normal_pdf(d1(opt)) * sigma_percent(opt)) / (-2.0 * std::sqrt(opt.time)) ) \
				- (opt.interest * opt.strike * std::exp(-1.0 * opt.interest * opt.time) * normal_cdf(d2(opt))) ;
}

constexpr double put_theta(const Option& opt)
{	
	return 	( (opt.spot[0] * normal_pdf(d1(opt)) * sigma_percent(opt)) / (-2.0 * std::sqrt(opt.time)) ) \
				+ (opt.interest * opt.strike * std::exp(-1.0 * opt.interest * opt.time) * normal_cdf(-d2(opt))) ;
}

constexpr double call_rho(const Option& opt)
{	
	return opt.strike * opt.time * std::exp(-1.0 * opt.interest * opt.time) * normal_cdf(d2(opt)) ;
}

constexpr double put_rho(const Option& opt)
{	
	return -opt.strike * opt.time * std::exp(-1.0 * opt.interest * opt.time) * normal_cdf(-d2(opt)) ;
}


