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

CalcBaselineTrivial::CalcBaselineTrivial(std::vector<double> yv, double time_from, double time_to, double HORIZ_INTERVAL)
{
	const int n_points_from = time_from / HORIZ_INTERVAL;
	const int n_points_to = time_to / HORIZ_INTERVAL;

	baseline = 0;
	for (int i = n_points_from; i < n_points_to; i++)
	{
		baseline += yv[i];
	}

	baseline /= (n_points_to - n_points_from);
}


CalcBaselineTrivial::~CalcBaselineTrivial()
{
}
