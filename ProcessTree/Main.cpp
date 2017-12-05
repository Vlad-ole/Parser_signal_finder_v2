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
#include "TSystem.h"
#include "TGraph.h"

//my
#include "RunDescription.h"

using namespace std;


void wait(int n_sec, bool is_infinite = false)
{
	if (is_infinite)
	{
		char c;
		std::cout << "press esc to exit! " << std::endl;
		
		while (true)
		{
			c = _getch();
			if (c == 27)
				break;

			gSystem->ProcessEvents();			
			gSystem->Sleep(100);
		}		
	}
	else
	{
		std::cout << "programm will be closed in " << n_sec << " sec" << std::endl;
		for (int i = 0; i < (n_sec * 10); ++i)
		{
			gSystem->ProcessEvents();
			gSystem->Sleep(100);
		}
	}
	
	std::cout << "exited. " << std::endl;
}

//---------------------------------------------
//braches info for tree_raw
std::vector<double> *data_raw = 0;
std::vector<double> *data_der = 0;
std::vector<double> *data_without_slope = 0;
double min_element;
double max_element;
double baseline;
int run_id;
int event_id;
int ch_id;
//---------------------------------------------


//---------------------------------------------
//braches info for tree_info
double HORIZ_INTERVAL; //in ns
int WAVE_ARRAY_COUNT;
int runs_per_tree_file;
int N_ch;
int n_blocks;
//---------------------------------------------



//---------------------------------------------
//braches info for tree_intermediate
double num_of_pe_in_event__positive_part_s_int;
std::vector<int> *signals_x_start = 0;
std::vector<int> *signals_x_stop = 0;
std::vector<double> *local_baseline = 0;
std::vector<double> *integral_one_peak = 0;
std::vector<double> *one_peak_y_maximum = 0;
std::vector<double> *num_of_pe_in_one_peak = 0;
//---------------------------------------------



int main(int argc, char *argv[])
{
	TStopwatch timer_total;
	timer_total.Start();

	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	//gROOT->SetBatch(kTRUE);


	//---------------------------------------------
	//tree_info
	ostringstream f_tree_info_name;
	f_tree_info_name << path_name_tree << "tree_info.root";

	TFile *f_tree_info = new TFile(f_tree_info_name.str().c_str());
	TTree *tree_info = (TTree*)f_tree_info->Get("tree_info");

	tree_info->SetBranchAddress("HORIZ_INTERVAL", &HORIZ_INTERVAL);
	tree_info->SetBranchAddress("WAVE_ARRAY_COUNT", &WAVE_ARRAY_COUNT);
	tree_info->SetBranchAddress("runs_per_tree_file", &runs_per_tree_file);
	tree_info->SetBranchAddress("n_ch", &N_ch);
	tree_info->SetBranchAddress("n_blocks", &n_blocks);

	tree_info->GetEntry(0);
	f_tree_info->Close();//hmmmm
	//---------------------------------------------



	//---------------------------------------------
	//tree_itermediate
	ostringstream f_tree_itermediate_name;
	f_tree_itermediate_name << path_name_tree << "tree_intermediate.root";

	TFile *f_tree_itermediate = new TFile(f_tree_itermediate_name.str().c_str());
	TTree *tree_itermediate = (TTree*)f_tree_itermediate->Get("tree_intermediate");

	tree_itermediate->SetBranchAddress("num_of_pe_in_event__positive_part_s_int", &num_of_pe_in_event__positive_part_s_int);
	tree_itermediate->SetBranchAddress("signals_x_start", &signals_x_start);
	tree_itermediate->SetBranchAddress("signals_x_stop", &signals_x_stop);
	tree_itermediate->SetBranchAddress("local_baseline", &local_baseline);
	tree_itermediate->SetBranchAddress("integral_one_peak", &integral_one_peak);
	tree_itermediate->SetBranchAddress("one_peak_y_maximum", &one_peak_y_maximum);
	tree_itermediate->SetBranchAddress("num_of_pe_in_one_peak", &num_of_pe_in_one_peak);		
	//---------------------------------------------


	//---------------------------------------------
	//tree_raw
	vector<TChain*> chain_v;
	for (int i = 0; i < N_ch; i++)
	{
		TChain *chain = new TChain("tree_raw");
		for (int counter_f_tree = 0; counter_f_tree < n_blocks; counter_f_tree++)
		{
			ostringstream f_tree_name;
			f_tree_name << path_name_tree << "ch_" << GetChId(i) << "__block_" << setfill('0') << setw(7) << counter_f_tree << ".root";
			chain->Add(f_tree_name.str().c_str());
			//chain.Show();
		}

		chain_v.push_back(chain);
		//chain_v[i]->Show();
	}
	//---------------------------------------------

	//-----------------------------------
	//SetBranchAddress
	chain_v[3]->SetBranchAddress("data_raw", &data_raw);
	chain_v[3]->SetBranchAddress("data_der", &data_der);
	chain_v[3]->SetBranchAddress("data_without_slope", &data_without_slope);

	chain_v[3]->SetBranchAddress("min_element", &min_element);
	chain_v[3]->SetBranchAddress("max_element", &max_element);
	chain_v[3]->SetBranchAddress("baseline", &baseline);

	chain_v[3]->SetBranchAddress("run_id", &run_id);
	chain_v[3]->SetBranchAddress("event_id", &event_id);
	chain_v[3]->SetBranchAddress("ch_id", &ch_id);
	//-----------------------------------



	//tree_itermediate->GetEntry(0);

	
	//Npe_sipm_matrix
	TH1F *hist = new TH1F("hist", "hist", 100, 0.1, 600);

	tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);

	const int n_events = tree_itermediate->GetEntries();
	cout << "n_events = " << n_events << endl;
	for (int i = 0; i < n_events; i++)
	{
		double val = 0;
		tree_itermediate->GetEntry(i);
		chain_v[3]->GetEntry(i);
		if (i % 1000 == 0)
		{
			cout << "event = " << i << " (" << (100 * i / (double)n_events) << " %)" << endl;
		}

		cout << "ch_id = " << ch_id << endl;
	}


	{
		//int n_events;
		////loop by chs
		//for (int i = 0; i < N_ch; i++)
		//{
		//	if (GetChId(i) < 3) //process only SiPM ch
		//		continue;
		//
		//	
		//	TChain chain("tree_raw");
		//	const int n_blocks = 1;
		//	for (int counter_f_tree = 0; counter_f_tree < n_blocks; counter_f_tree++)
		//	{
		//		ostringstream f_tree_name;
		//		f_tree_name << path_name_tree << "ch_" << GetChId(i) << "__block_" << setfill('0') << setw(7) << counter_f_tree << ".root";
		//		chain.Add(f_tree_name.str().c_str());
		//	}
		//	n_events = chain.GetEntries();
		//	cout << "i = " << i << "; ch_id = " << GetChId(i) << "; GetEntries = " << n_events << endl;
	}

	//	//-----------------------------------
	//	//SetBranchAddress
	//	chain.SetBranchAddress("data_raw", &data_raw);
	//	chain.SetBranchAddress("data_der", &data_der);
	//	chain.SetBranchAddress("data_without_slope", &data_without_slope);

	//	chain.SetBranchAddress("min_element", &min_element);
	//	chain.SetBranchAddress("max_element", &max_element);
	//	chain.SetBranchAddress("baseline", &baseline);
	//	//-----------------------------------

	//}


	f_tree_itermediate->Close();
	timer_total.Stop();	
	//wait(0, true);
	
	//cout << "n_events = " << n_events << endl;
	cout << "total time = " << timer_total.RealTime() << " sec" << endl;
	cout << "all is ok" << endl;


	system("pause");
	theApp.Terminate();
	theApp.Run();

	return 0;

}