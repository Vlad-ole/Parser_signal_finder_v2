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

class TreeRaw
{
public:
	TreeRaw();
	~TreeRaw();

	TTree* GetTreePnt();

	int run_number;
	int event_id;
	int ch_id;

//private:
	TTree *tree;
	std::vector<double> data_raw;
	std::vector<double> data_der;
	std::vector<double> data_without_slope;

	double min_element;
	double max_element;
	double baseline;
	
};

