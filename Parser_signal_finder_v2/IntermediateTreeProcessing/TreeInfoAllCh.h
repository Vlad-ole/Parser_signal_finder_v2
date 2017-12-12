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

class TreeInfoAllCh
{
public:
	TreeInfoAllCh();
	~TreeInfoAllCh();

	TTree *tree;

	double num_of_pe_in_event_all_ch__positive_part_s_int;
	double x_cog;
	double y_cog;
};

