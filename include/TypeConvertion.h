#pragma once

#include <iostream>
#include <vector>

class TypeConvertion
{
public:
	TypeConvertion();
	~TypeConvertion();
	static std::vector<float> GetVectorFloat(std::vector<double> & yv_double);
	static std::vector<double> GetVectorDouble(std::vector<float> & yv_float);

	static std::vector<double> GetVectorFromScalar(int size, double scalar);
	static std::vector<double> GetVectorMultiplyToScalar(std::vector<double> & yv_double, double scalar);
	
	static std::vector<double> GetVectorDoubleInvert(std::vector<double> & yv_double);
	static std::vector<double> GetDifference(std::vector<double> yv_minuend, std::vector<double> yv_subtrahend);
	static std::vector<double> GetDifference(std::vector<double> yv_minuend, double y_subtrahend);

	static std::vector<double> TypeConvertion::GetSumm(std::vector<double> yv_summ1, std::vector<double> yv_summ2);
private:

};

