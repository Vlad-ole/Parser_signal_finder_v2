#include "CalcBaseline.h"

CalcBaseline::CalcBaseline()
{
}


CalcBaseline::~CalcBaseline()
{
}

double CalcBaseline::GetBaseline()
{
	return baseline;
}

std::vector<double>& CalcBaseline::GetBaselineVec()
{
	return baseline_vec;
}
