#include "TypeConvertion.h"
#include <assert.h> 

TypeConvertion::TypeConvertion()
{
}


TypeConvertion::~TypeConvertion()
{
}

std::vector<double> TypeConvertion::GetVectorMultiplyToScalar(std::vector<double> & yv_double, double scalar)
{
	std::vector<double> vec(yv_double.size());
	for (int i = 0; i < yv_double.size(); i++)
	{
		vec[i] = yv_double[i] * scalar;
	}
	
	return vec;
}


std::vector<double> TypeConvertion::GetVectorFromScalar(int size, double scalar)
{
	std::vector<double> vec(size);
	for (int i = 0; i < size; i++)
	{
		vec[i] = scalar;
	}

	return vec;
}

std::vector<float> TypeConvertion::GetVectorFloat(std::vector<double>& yv_double)
{
	std::vector<float> yv_float(yv_double.size());
	for (int i = 0; i < yv_double.size(); i++)
	{
		yv_float[i] = yv_double[i];
	}

	return yv_float;
}

std::vector<double> TypeConvertion::GetVectorDouble(std::vector<float>& yv_float)
{
	std::vector<double> yv_double(yv_float.size());
	for (int i = 0; i < yv_float.size(); i++)
	{
		yv_double[i] = yv_float[i];
	}

	return yv_double;
}

std::vector<double> TypeConvertion::GetVectorDoubleInvert(std::vector<double> & yv_double)
{
	std::vector<double> yv_double_invert(yv_double.size());
	for (int i = 0; i < yv_double.size(); i++)
	{
		yv_double_invert[i] = -yv_double[i];
	}

	return yv_double_invert;
}

std::vector<double> TypeConvertion::GetDifference(std::vector<double> yv_minuend, std::vector<double> yv_subtrahend)
{
	//assert(yv_minuend.size() != yv_subtrahend.size() && "Error! yv_minuend.size() == yv_subtrahend.size()");
	std::vector<double> result(yv_minuend.size());
	for (int i = 0; i < yv_minuend.size(); i++)
	{
		result[i] = yv_minuend[i] - yv_subtrahend[i];
	}

	return result;
}

std::vector<double> TypeConvertion::GetDifference(std::vector<double> yv_minuend, double y_subtrahend)
{
	std::vector<double> result(yv_minuend.size());
	for (int i = 0; i < yv_minuend.size(); i++)
	{
		result[i] = yv_minuend[i] - y_subtrahend;
	}

	return result;
}

std::vector<double> TypeConvertion::GetSumm(std::vector<double> yv_summ1, std::vector<double> yv_summ2)
{
	//assert(yv_minuend.size() != yv_subtrahend.size() && "Error! yv_minuend.size() == yv_subtrahend.size()");
	std::vector<double> result(yv_summ1.size());
	for (int i = 0; i < yv_summ1.size(); i++)
	{
		result[i] = yv_summ1[i] + yv_summ2[i];
	}

	return result;
}