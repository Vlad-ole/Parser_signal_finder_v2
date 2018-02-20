#pragma once

//c++
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <conio.h>

//root cern
#include "TApplication.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
#include "TGraph.h"
#include "TCut.h"
#include "TGraph2D.h"
#include "TRandom3.h"
#include "TCanvas.h"

//my
#include "RunDescription.h"
#include "ChCharacteristics.h"
#include "Singleton.h"

class Simple_MC
{
public:
	Simple_MC(TGraph2D* gr2D, bool is_draw = true, int N_runs = 1);
	~Simple_MC();

	void Calc_MC();
	void Calc_center_shift();
private:
	double h_x; // диаметр источника [mm]
	double h_c;//1
	double l_x;
	double lambda_bar;
	double lambda;
	TRandom3 rnd3;

	ofstream file_out;
	int N_runs;
	TGraph2D* gr2D;
	TH2D *h2D;

	double PMMA_width;
	double LAr_dead_width;
	double THGEM_Cathode_width;
	double Al_window_width;

	double x_center_shift;
	double y_center_shift;

	int N_ch;
	bool is_draw;
};

