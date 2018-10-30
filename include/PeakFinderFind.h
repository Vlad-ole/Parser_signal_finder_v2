#pragma once
#include "PeakFinderBase.h"


class PeakFinderFind :
	public PeakFinderBase
{
public:
	//PeakFinderFind(std::vector<double>& yv, std::vector<double>& yv_der, const double th, const double th_der, const double HORIZ_INTERVAL);
	PeakFinderFind::PeakFinderFind(std::vector<double>& yv, std::vector<double>& yv_der, const double th, const double th_der, const double HORIZ_INTERVAL, bool is_by_amp);
	~PeakFinderFind();
};

