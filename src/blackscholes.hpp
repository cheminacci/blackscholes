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

double sigma(Option& opt);

double normal_cdf(const double& x); 	

double normal_pdf(const double& x); 

double call_option_price(Option& opt);	


