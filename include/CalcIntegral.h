#pragma once

#include <iostream>
#include <vector>

class CalcIntegral
{
public:
	CalcIntegral(std::vector<double> data, std::vector<double> baseline_v,
		const double time_from, const double time_to, const double time_scale);

	CalcIntegral(std::vector<double> data, double baseline, std::vector<double> baseline_v,
		const double time_from, const double time_to, const double time_scale);
	
	CalcIntegral(std::vector<double> data, double baseline,
		const double time_from, const double time_to, const double time_scale);

	CalcIntegral(std::vector<double> data, const double time_scale, const int N_poitns_below_0);

	
	
	~CalcIntegral();

	int GetPointTo();
	double GetIntegrtal();
private:
	double integral;
	int point_from;
	int point_to;
};

