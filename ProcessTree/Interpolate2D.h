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


#pragma once
class Interpolate2D
{
public:
	Interpolate2D(TGraph2D* gr2d);
	~Interpolate2D();

	double GetValueLine(double x, double y);
	double GetValueBicubic(double x, double y);

private:
	TGraph2D* gr2d;
};

