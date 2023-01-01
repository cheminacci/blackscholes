// blackscholes.hpp

#pragma once

#include "scinge.hpp"
#include <cmath>
#include <numbers>
#include <random>
#include <iostream>
#include <array>

struct Option
{
	std::array<double, 15> spot;			
	double strike;		
	double interest;		
	double time;	
};


using std::numbers::pi;

constexpr double sigma(const Option& opt)
{	
	return scinge::standard_deviation(opt.spot); 
}

constexpr double sigma_percent(const Option& opt)
{	
	return (scinge::standard_deviation(opt.spot)) / scinge::average(opt.spot); 
}

/*

constexpr double delta(Option &opt);
{	return 0.0;	}

constexpr double gamma(Option &opt);
{	return 0.0;	}

constexpr double theta(Option &opt);
{	return 0.0;	}

constexpr double vega(Option &opt);
{	return 0.0;	}

constexpr double rho(Option& opt);
{	return 0.0;	}

*/


constexpr double normal_cdf(const double& x)
{
	const double k = 1.0 / (1.0 + 0.2316419 * x);
    const double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) 
	{	return ( 1.0 - (1.0 / (pow(2 * pi, 0.5))) * exp(-0.5 * x * x) * k_sum ) ;}
	else 
	{	return (1.0 - normal_cdf(-x)); }
}

	

constexpr double my_normal_cdf(const double& x, const double& mean, const double& sigma)
{	
	// return ( 1.0 / (sigma * sqrt(2*pi)) ) * exp( -0.5 * pow(((x - mean) / sigma) , 2) ) ;
	return ( 0.5 * (1.0 + std::erfc( (x - mean) / (sigma * sqrt(2)) )) );
}


constexpr double normal_pdf(const double& x)
{	
	return ( (1.0 / (pow((pi * 2), -0.5))) * exp(-0.5 * x * x) ); 
}


double call_option_price(const Option& opt)
{
	const double sig_p = sigma_percent(opt);
//  const double spot_av = scinge::average(opt.spot);

	const double d1 = ( log(opt.spot[0]/opt.strike) + ((opt.interest + (pow(sig_p,2)/2)) * opt.time) ) / ( sig_p * sqrt(opt.time) );
	const double d2 = ( d1 - (sig_p * sqrt(opt.time)) ); 

	const double nd1 = normal_cdf(d1);
	const double nd2 = normal_cdf(d2);
//	const double nd1 = my_normal_cdf(d1, spot_av, sig_p);
//	const double nd2 = my_normal_cdf(d2, spot_av, sig_p);

	std::cout << "\nd1 is ...\t" << d1 << std::endl;
	std::cout << "d2 is ...\t" << d2 << std::endl;
	std::cout << "N(d1) is ...\t" << nd1 << std::endl;
	std::cout << "N(d2) is ...\t" << nd2 << std::endl;

	return  ( nd1 * opt.spot[0] ) - ( opt.strike * exp(-1 * opt.interest * opt.time) * nd2 ) ;
}


double put_option_price(const Option& opt)
{
		return ( opt.strike * exp(-1 * opt.interest * opt.time) ) - opt.spot[0] + call_option_price(opt) ;
}


