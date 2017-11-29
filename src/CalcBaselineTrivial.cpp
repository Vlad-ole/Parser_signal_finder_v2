#include "CalcBaselineTrivial.h"


CalcBaselineTrivial::CalcBaselineTrivial(std::vector<double> yv, double time, double HORIZ_INTERVAL)
{
	const int n_points = time / HORIZ_INTERVAL;

	baseline = 0;
	for (int i = 0; i < n_points; i++)
	{
		baseline += yv[i];
	}

	baseline /= n_points;
}


CalcBaselineTrivial::~CalcBaselineTrivial()
{
}
