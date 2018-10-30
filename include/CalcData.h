#pragma once

//c++
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

//root cern
#include "TApplication.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TTree.h"

//my
#include "CalcBaselineZeroComp.h"

class CalcData
{
public:
	CalcData(std::vector<double> &data_raw, double HORIZ_INTERVAL, bool is_invert);
	~CalcData();

	double Get_min_element();
	double Get_max_element();

	std::vector<double> Get_data_der();
	std::vector<double> Get_data_without_slope();

	double CalcData::Get_baseline();

private:
	std::vector<double> &data_raw;
	const bool is_invert;
	std::vector<double> invert_data;
	std::vector<double> baseline_vec;
	CalcBaselineZeroComp *calc_baseline_zero_comp;

	double baseline;

	const double HORIZ_INTERVAL;
};

