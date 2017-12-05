#pragma once

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

	TTree *tree;

	double HORIZ_INTERVAL; //in ns
	int WAVE_ARRAY_COUNT;
	int runs_per_tree_file;
	int n_ch;
	int n_blocks;
};

