#include "TypeConvertion.h"
#include <assert.h> 

TypeConvertion::TypeConvertion()
{
}


TypeConvertion::~TypeConvertion()
{
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