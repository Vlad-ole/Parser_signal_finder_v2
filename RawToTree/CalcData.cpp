#include <algorithm>

//my
#include "CalcDer.h"
#include "CalcData.h"
#include "TypeConvertion.h"

using namespace std;

CalcData::CalcData(std::vector<double> &data_raw) : data_raw(data_raw)
{
}


CalcData::~CalcData()
{
}

double CalcData::Get_min_element()
{
	return *min_element(data_raw.begin(), data_raw.end());
}

double CalcData::Get_max_element()
{
	return *max_element(data_raw.begin(), data_raw.end());
}

std::vector<double> CalcData::Get_data_der(bool is_invert)
{
	if (is_invert)
	{
		CalcDer calc_der_tmp(TypeConvertion::GetVectorDoubleInvert(data_raw), 101, 1);
		return calc_der_tmp.GetDer();
	}
	else
	{
		CalcDer calc_der_tmp(data_raw, 101, 1);
		return calc_der_tmp.GetDer();
	}	
	
}