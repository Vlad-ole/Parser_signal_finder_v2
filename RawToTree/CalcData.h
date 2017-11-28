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
	CalcData(std::vector<double> &data_raw);
	~CalcData();

	double Get_min_element();
	double Get_max_element();

	std::vector<double> Get_data_der(bool is_invert = false);

private:
	std::vector<double> &data_raw;
};

