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

class IntermediateTreeInfo
{
public:
	IntermediateTreeInfo();
	~IntermediateTreeInfo();

	TTree *tree;
	double num_of_pe_in_event__positive_part_s_int;
	std::vector<int> signals_x_start;
	//std::vector<int> signals_x_stop;
	//std::vector<double> local_baseline;
	//std::vector<double> integral_one_peak;
	//std::vector<double> one_peak_y_maximum;
	//
	//std::vector<double> num_of_pe_in_one_peak;	
};

