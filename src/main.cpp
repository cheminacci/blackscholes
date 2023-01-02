#include "blackscholes.hpp"
#include <iostream>

int main()
{
	Option sbux;
	sbux.spot = {101.50, 105.23, 100.33, 102.75, 107.88, 104.45, 103.11, 100.99, 99.77, 100.75, 99.99, 97.34, 100.10, 110.35, 120.77};
	
	std::cout << "\nWhat is the strike price for the option: ----->\t";
	std::cin >> sbux.strike;

	std::cout << "\nPlease enter the risk free interest rate: ----->\t";
	std::cin >> sbux.interest;

	std::cout << "\nPlease enter the time left until maturity (in years): ------>\t";
	std::cin >> sbux.time;
	

	std::cout << "\nThe current spot price is:\t" << sbux.spot[0] << '\n';
	std::cout << "This spot average is:\t" << scinge::average(sbux.spot) << '\n';
	std::cout << "The strike price is:\t" << sbux.strike << '\n';
	std::cout << "The risk free interest rate is:\t" << sbux.interest << '\n';
	std::cout << "The time to maturity is:\t" << sbux.time << " years.\n";
	std::cout << "The current 8 period moving average is:\t" << scinge::moving_average(sbux.spot, 8, 0) << '\n';
	std::cout << "The current volatility of the asset (sigma) is:\t" << sigma(sbux) << '\n';
	std::cout << "The current volatility percentage is:\t" << sigma_percent(sbux) << '\n';
	std::cout << "\nThe call option price for sbux is:\t" << call_option_price(sbux) << '\n';
	std::cout << "The put option price for sbux is:\t" << put_option_price(sbux) << '\n';

	return 0;
}
