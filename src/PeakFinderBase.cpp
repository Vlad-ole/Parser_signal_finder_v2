#include "PeakFinderBase.h"

using namespace std;

PeakFinderBase::PeakFinderBase()
{
}


PeakFinderBase::~PeakFinderBase()
{
}

std::vector<std::pair<int, int>> PeakFinderBase::GetPeakPositions()
{
	return pair_v;
}

std::vector<double> PeakFinderBase::GetLocalBaselineV()
{
	return local_baseline_v;
}