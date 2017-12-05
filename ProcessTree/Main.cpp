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
#include  "TypeConvertion.h"

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


TChain* chain_all_ch;
TTree *tree_itermediate;

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

void Npe_sipm_matrix()
{
	//Npe_sipm_matrix
	TH1F *hist = new TH1F("hist", "hist", 100, 0.1, 600);
	const int ch_to_process = 38;
	const int array_position = GetArrayPosition(ch_to_process);

	tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);

	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);

	const int n_events = tree_itermediate->GetEntries();
	cout << "tree_itermediate->GetEntries() = " << n_events << endl;
	cout << "chain_all_ch->GetEntries() = " << chain_all_ch->GetEntries() << endl;

	chain_all_ch->GetEntry(0);
	cout << ch_id << "; " << run_id << "; " << event_id << "; " << num_of_pe_in_event__positive_part_s_int << endl;

	for (int i = 0; i < n_events; i++)
	{
		double val = 0;
		tree_itermediate->GetEntry(i);
		chain_all_ch->GetEntry(i);
		if (i % 1000 == 0)
		{
			cout << "event = " << i << " (" << (100 * i / (double)n_events) << " %)" << endl;
		}

		if (ch_id == ch_to_process)
		{
			hist->Fill(num_of_pe_in_event__positive_part_s_int);
			cout << ch_id << "; " << run_id << "; " << event_id << "; " << num_of_pe_in_event__positive_part_s_int << endl;
		}

	}

	hist->Draw();
}

void Show_individual_signals()
{
	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);
	chain_all_ch->SetBranchStatus("baseline", 1);

	vector<double> time(WAVE_ARRAY_COUNT);
	for (int i = 0; i < time.size(); i++)
	{
		time[i] = i * HORIZ_INTERVAL;
	}

	const int n_events = chain_all_ch->GetEntries();
	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);

		if (i % 1000 == 0 || i == (n_events - 1))
		{
			double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
			cout << "event = " << i << " (" << val << " %)" << endl;
		}


		if (ch_id == 38 && run_id == 8 && event_id == 0)
		{
			chain_all_ch->SetBranchStatus("data_der", 1);
			chain_all_ch->SetBranchAddress("data_der", &data_der);
			chain_all_ch->GetEntry(i);

			TGraph *gr = new TGraph(WAVE_ARRAY_COUNT, &time[0], &((*data_der)[0]));
			gr->SetTitle("data_der");
			gr->SetMarkerStyle(20);
			gr->SetMarkerSize(1);
			gr->SetLineColor(kPink);
			gr->Draw("ALP");

			/*TGraph *gr_2 = new TGraph(WAVE_ARRAY_COUNT, &time[0], &(TypeConvertion::GetVectorFromScalar(WAVE_ARRAY_COUNT, baseline))[0]);
			gr_2->SetLineColor(kGreen);
			gr_2->Draw("same L");*/

			break;
		}
	}
}

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
	tree_itermediate = (TTree*)f_tree_itermediate->Get("tree_intermediate");

	tree_itermediate->SetBranchAddress("num_of_pe_in_event__positive_part_s_int", &num_of_pe_in_event__positive_part_s_int);
	tree_itermediate->SetBranchAddress("signals_x_start", &signals_x_start);
	tree_itermediate->SetBranchAddress("signals_x_stop", &signals_x_stop);
	tree_itermediate->SetBranchAddress("local_baseline", &local_baseline);
	tree_itermediate->SetBranchAddress("integral_one_peak", &integral_one_peak);
	tree_itermediate->SetBranchAddress("one_peak_y_maximum", &one_peak_y_maximum);
	tree_itermediate->SetBranchAddress("num_of_pe_in_one_peak", &num_of_pe_in_one_peak);
	//---------------------------------------------



	//---------------------------------------------
	chain_all_ch = new TChain("tree_raw");
	for (int i = 0; i < N_ch; i++)
	{
		for (int counter_f_tree = 0; counter_f_tree < n_blocks; counter_f_tree++)
		{
			ostringstream f_tree_name;
			f_tree_name << path_name_tree << "ch_" << GetChId(i) << "__block_" << setfill('0') << setw(7) << counter_f_tree << ".root";
			chain_all_ch->Add(f_tree_name.str().c_str());
		}
	}

	//SetBranchAddress
	chain_all_ch->SetBranchAddress("data_raw", &data_raw);
	chain_all_ch->SetBranchAddress("data_der", &data_der);
	chain_all_ch->SetBranchAddress("data_without_slope", &data_without_slope);

	chain_all_ch->SetBranchAddress("min_element", &min_element);
	chain_all_ch->SetBranchAddress("max_element", &max_element);
	chain_all_ch->SetBranchAddress("baseline", &baseline);

	chain_all_ch->SetBranchAddress("run_id", &run_id);
	chain_all_ch->SetBranchAddress("event_id", &event_id);
	chain_all_ch->SetBranchAddress("ch_id", &ch_id);

	//---------------------------------------------

	Show_individual_signals();
	
	////Npe_sipm_matrix
	//TH1F *hist = new TH1F("hist", "hist", 100, 0.1, 600);
	//const int ch_to_process = 38;
	//const int array_position = GetArrayPosition(ch_to_process);

	//tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	//tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);

	//chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	//chain_all_ch->SetBranchStatus("ch_id", 1);
	//chain_all_ch->SetBranchStatus("run_id", 1);
	//chain_all_ch->SetBranchStatus("event_id", 1);

	//const int n_events = tree_itermediate->GetEntries();
	//cout << "tree_itermediate->GetEntries() = " << n_events << endl;
	//cout << "chain_all_ch->GetEntries() = " << chain_all_ch->GetEntries() << endl;

	//chain_all_ch->GetEntry(0);
	//cout << ch_id << "; " << run_id << "; " << event_id << "; " << num_of_pe_in_event__positive_part_s_int << endl;

	//for (int i = 0; i < n_events; i++)
	//{
	//	double val = 0;
	//	tree_itermediate->GetEntry(i);
	//	chain_all_ch->GetEntry(i);
	//	if (i % 1000 == 0)
	//	{
	//		cout << "event = " << i << " (" << (100 * i / (double)n_events) << " %)" << endl;
	//	}

	//	if (ch_id == ch_to_process)
	//	{
	//		hist->Fill(num_of_pe_in_event__positive_part_s_int);
	//		cout << ch_id << "; " << run_id << "; " << event_id << "; " << num_of_pe_in_event__positive_part_s_int << endl;
	//	}		

	//}
	
	
	cout << "all is ok" << endl;
	theApp.Run();

	f_tree_itermediate->Close();
	timer_total.Stop();	
	//wait(0, true);
	
	//cout << "n_events = " << n_events << endl;
	cout << "total time = " << timer_total.RealTime() << " sec" << endl;
	//cout << "all is ok" << endl;


	system("pause");
	//theApp.Terminate();
	//theApp.Run();

	return 0;

}