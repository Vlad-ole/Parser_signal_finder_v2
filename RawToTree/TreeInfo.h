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

class TreeInfo
{
public:
	TreeInfo();
	~TreeInfo();

	TTree* GetTreePnt();

	int run_number;
	int event_id;
	int ch_id;

//private:
	TTree *tree;	
};

