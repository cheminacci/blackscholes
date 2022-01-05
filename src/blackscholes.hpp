// blackscholes.hpp

#pragma once

#include "scinge.hpp"
#include <vector>
#include <cmath>
#include <numbers>
#include <random>
#include <iostream>
#include <fstream>

struct Option
{
	std::array<double, 15> spot_price;			
	double strike_price;		
	double interest_rate;		
	double time_to_maturity;	
};

constexpr double sigma(Option& opt);

constexpr double sigma_percent(Option& opt);

constexpr double normal_cdf(const double& x); 	

constexpr double normal_pdf(const double& x); 

constexpr double call_option_price(Option& opt);	


