#include "CalcIntegral.h"

#include <iostream>
using namespace std;

CalcIntegral::CalcIntegral(std::vector<double> data, std::vector<double> baseline,
	const double time_from, const double time_to, const double time_scale) :
	point_from(time_from / time_scale), point_to(time_to / time_scale)
{
	integral = 0;
	for (int i = point_from; i < point_to; i++)
	{
		integral += (data[i] - baseline[i]);
	}
	integral *= time_scale;
}

CalcIntegral::CalcIntegral(std::vector<double> data, double baseline,
	const double time_from, const double time_to, const double time_scale) :
	point_from(time_from / time_scale), point_to(time_to / time_scale)
{
	integral = 0;
	for (int i = point_from; i < point_to; i++)
	{
		integral += (data[i] - baseline);
	}

	integral *= time_scale;
}


CalcIntegral::CalcIntegral(std::vector<double> data, double baseline, std::vector<double> baseline_v,
	const double time_from, const double time_to, const double time_scale) :
	point_from(time_from / time_scale), point_to(time_to / time_scale)
{
	integral = 0;
	for (int i = point_from; i < point_to; i++)
	{
		integral += (-data[i] + 2 * baseline - baseline_v[i]);
	}
	integral *= time_scale;
}

//to caclulate double integral of positive part of integral
CalcIntegral::CalcIntegral(std::vector<double> data, const double time_scale, const int N_poitns_below_0)
{
	integral = 0;
	point_to = 0;

	for (int i = 0; i < (data.size() - 100); i++)
	{
		if (data[i] < 0 && data[i + 1] < 0 && data[i + 100] < -2*500 )
		{
			point_to = i;
			break;
		}

		integral += data[i];
	}

	integral *= time_scale;
}


CalcIntegral::~CalcIntegral()
{
}

int CalcIntegral::GetPointTo()
{
	return point_to;
}

double CalcIntegral::GetIntegrtal()
{
	return integral;
}
