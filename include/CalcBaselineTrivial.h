#pragma once
#include "CalcBaseline.h"
class CalcBaselineTrivial :
	public CalcBaseline
{
public:
	CalcBaselineTrivial(std::vector<double> yv, double time, double HORIZ_INTERVAL);
	virtual ~CalcBaselineTrivial();
};

