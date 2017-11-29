#pragma once

#include <iostream>
#include <vector>

class CalcDer
{
public:
	CalcDer(std::vector<double> yv, const int param_n_points, const int order_of_derivative /*0 = smooth, 1 = 1st derivative, etc.*/);
	~CalcDer();
	std::vector<double> GetDer();
private:
	void CalcDer::CalculateCoeffDer(int points, const int order_of_derivative);
	std::vector<double> yv_der;
	static std::vector<bool> is_first_obj;
	static std::vector< std::vector<double> > C_i_der;
};

