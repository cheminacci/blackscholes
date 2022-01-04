#include "blackscholes.cpp"
#include <iostream>

int main()
{
	Option sbux;
	sbux.spot_price = {100.50, 101.23, 100.33, 102.75, 102.88, 101.45, 100.11, 99.99, 99.77, 100.75, 99.99, 101.34, 100.10, 100.35, 100.77};
	sbux.interest_rate = 0.05;
	sbux.time_to_maturity = 1.0;
	sbux.strike_price = 100.0;

	std::cout << "The current spot price is:\t" << sbux.spot_price[0] << '\n';
	std::cout << "The strike price is:\t" << sbux.strike_price << '\n';
	std::cout << "The risk free interest rate is:\t" << sbux.interest_rate << '\n';
	std::cout << "The time to maturity is:\t" << sbux.time_to_maturity << '\n';
	std::cout << "The current 8 period moving average is:\t" << scinge::moving_average(sbux.spot_price, 8, 0) << '\n';
	std::cout << "The current volatility of the asset (sigma) is:\t" << sigma(sbux) << '\n';
	std::cout << "The call option price for sbux is:\t" << call_option_price(sbux) << '\n';
	std::cout << "The put option price for sbux is:\t" << put_option_price(sbux) << '\n';

	return 0;
}
