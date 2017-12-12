#include <algorithm>

//my
#include "CalcDer.h"
#include "CalcData.h"
#include "TypeConvertion.h"
#include "CalcBaselineZeroComp.h"
#include "CalcBaselineTrivial.h"

using namespace std;

CalcData::CalcData(std::vector<double> &data_raw, double HORIZ_INTERVAL, bool is_invert) : data_raw(data_raw), is_invert(is_invert), HORIZ_INTERVAL(HORIZ_INTERVAL)
{
	if (is_invert)
	{
		invert_data = TypeConvertion::GetVectorDoubleInvert(data_raw);
	}

	CalcBaselineTrivial calc_baseline(data_raw, 30000, HORIZ_INTERVAL);
	baseline = calc_baseline.GetBaseline();
}


CalcData::~CalcData()
{
}

double CalcData::Get_baseline()
{
	return baseline;
}

double CalcData::Get_min_element()
{
	return *min_element(data_raw.begin(), data_raw.end());
}

double CalcData::Get_max_element()
{
	return *max_element(data_raw.begin(), data_raw.end());
}

std::vector<double> CalcData::Get_data_der()
{
	const int n_points = 21;
	if (is_invert)
	{
		CalcDer calc_der_tmp(invert_data, n_points, 1);
		return calc_der_tmp.GetDer();
	}
	else
	{
		CalcDer calc_der_tmp(data_raw, n_points, 1);
		return calc_der_tmp.GetDer();
	}	
	
}

std::vector<double> CalcData::Get_data_without_slope()
{
	CalcBaselineZeroComp calc_baseline_zero_comp(invert_data, /*0*/ 35000, /*HORIZ_INTERVAL * 9999*/ 100000 , -baseline, HORIZ_INTERVAL);
	return TypeConvertion::GetDifference(invert_data, calc_baseline_zero_comp.GetBaselineVec());
}