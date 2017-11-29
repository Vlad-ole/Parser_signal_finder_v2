#pragma once
#include "CalcBaseline.h"
#include "TSpectrum.h"

class CalcBaselineZeroComp :
	public CalcBaseline
{
public:
	CalcBaselineZeroComp(std::vector<double> yv, const int time_left, const int time_right,
		const double baseline, double HORIZ_INTERVAL);
	virtual ~CalcBaselineZeroComp();
protected:
	TSpectrum *s;
};

