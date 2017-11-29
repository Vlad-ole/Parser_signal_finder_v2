#pragma once

#include <iostream>
#include <vector>



class CalcBaseline
{
public:
	CalcBaseline();
	virtual ~CalcBaseline() = 0;

	double GetBaseline();
	std::vector<double>& GetBaselineVec();
protected:
	double baseline;
	std::vector<double> baseline_vec;
};

