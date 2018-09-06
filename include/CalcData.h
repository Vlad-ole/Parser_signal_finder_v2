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

class CalcData
{
public:
	CalcData(std::vector<double> &data_raw, double HORIZ_INTERVAL, bool is_invert);
	~CalcData();

	double Get_min_element();
	double Get_max_element();

	double Get_pos_point_min_element();
	double Get_pos_point_max_element();

	std::vector<double> Get_data_der();
	std::vector<double> Get_data_without_slope();

	double CalcData::Get_baseline();
	double CalcData::Get_baseline_end();


private:
	std::vector<double> &data_raw;
	const bool is_invert;
	std::vector<double> invert_data;
	std::vector<double> baseline_vec;

	double baseline;
	double baseline_end;

	const double HORIZ_INTERVAL;
};

