#include "blackscholes.hpp"
#include <iostream>

int main()
{
	Option sbux;
	sbux.spot_price = {101.50, 105.23, 100.33, 102.75, 107.88, 104.45, 103.11, 100.99, 99.77, 100.75, 99.99, 97.34, 100.10, 110.35, 120.77};


	std::cout << "\nPlease enter the risk free interest rate: ----->\t";
	std::cin >> sbux.interest_rate;
	std::cout << "\nPlease enter the time left until maturity: ------>\t";
	std::cin >> sbux.time_to_maturity;
	std::cout << "\nWhat is the strike price for the option: ----->\t";
	std::cin >> sbux.strike_price;

	std::cout << "\nThe current spot price is:\t" << sbux.spot_price[0] << '\n';
	std::cout << "The strike price is:\t" << sbux.strike_price << '\n';
	std::cout << "The risk free interest rate is:\t" << sbux.interest_rate << '\n';
	std::cout << "The time to maturity is:\t" << sbux.time_to_maturity << '\n';
	std::cout << "The current 8 period moving average is:\t" << scinge::moving_average(sbux.spot_price, 8, 0) << '\n';
	std::cout << "The current volatility of the asset (sigma) is:\t" << sigma(sbux) << '\n';
	std::cout << "The current volatility percentage is:\t" << sigma_percent(sbux) << '\n';
	std::cout << "The call option price for sbux is:\t" << call_option_price(sbux) << '\n';
	std::cout << "The put option price for sbux is:\t" << put_option_price(sbux) << '\n';

	return 0;
}
