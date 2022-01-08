// blackscholes.cpp

#include "blackscholes.hpp"

constexpr double sigma(Option& opt);

constexpr double sigma_percent(Option& opt);

constexpr double delta(Option &opt);

constexpr double gamma(Option &opt);

constexpr double theta(Option &opt);

constexpr double vega(Option &opt);

constexpr double rho(Option& opt);

constexpr double normal_cdf(const double& x); 	

constexpr double my_normal_cdf(const double& x, const double& mean, const double& sigma);

constexpr double normal_pdf(const double& x); 

constexpr double call_option_price(Option& opt);	

constexpr double put_option_price(Option& opt);
