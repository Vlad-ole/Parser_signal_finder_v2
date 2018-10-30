#include "CalcBaselineZeroComp.h"
#include "TypeConvertion.h"

#include <iostream>
using namespace std;

CalcBaselineZeroComp::CalcBaselineZeroComp(std::vector<double> yv, const int time_left, const int time_right, const double baseline, double HORIZ_INTERVAL)
{
	const int yv_size = yv.size();
	baseline_vec.resize(yv_size);

	const int point_left = time_left / HORIZ_INTERVAL;
	const int point_right = time_right / HORIZ_INTERVAL;
	
	std::vector<float> yv_float = TypeConvertion::GetVectorFloat(yv);
	s = new TSpectrum();
	s->Background(&yv_float[point_left], point_right+1 - point_left , 50, TSpectrum::kBackIncreasingWindow, TSpectrum::kBackOrder2, kTRUE, TSpectrum::kBackSmoothing3, kFALSE);

	baseline_vec = TypeConvertion::GetVectorDouble(yv_float);

	for (int i = 0; i < point_left; i++)
	{
		baseline_vec[i] = baseline;
	}
	for (int i = point_right; i < yv_size; i++)
	{
		baseline_vec[i] = baseline;
	}
}


CalcBaselineZeroComp::~CalcBaselineZeroComp()
{
	delete s;
}
