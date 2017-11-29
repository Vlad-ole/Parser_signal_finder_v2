#pragma once

#include <iostream>
#include <vector>

class PeakFinderBase
{
public:
	PeakFinderBase();
	virtual ~PeakFinderBase();
	std::vector<std::pair<int, int>> GetPeakPositions();
	std::vector<double> GetLocalBaselineV();
protected:
	std::vector<std::pair<int, int>> pair_v;
	std::vector<double> local_baseline_v;
};

