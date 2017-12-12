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
#include "TCut.h"

//my
#include "RunDescription.h"
#include  "TypeConvertion.h"

using namespace std;

#define COUT(x) cout << #x " = " << x << endl;

string cut_condition_srt;
bool cut_condition_bool = false;
TCut total_cut;
#define REMEMBER_CUT(x) cut_condition_srt = #x; cut_condition_bool = x; total_cut = cut_condition_srt.c_str();

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
TTree *TreeInfoAllCh_tree;

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
int n_events_per_file;
int run_from;
int run_to;
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



//---------------------------------------------
//braches info for TreeInfoAllCh
double num_of_pe_in_event_all_ch__positive_part_s_int;
double x_cog;
double y_cog;
//---------------------------------------------


void Npe_sipm_one_ch()
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
		
		chain_all_ch->GetEntry(i);
		if (i % 1000 == 0)
		{
			cout << "event = " << i << " (" << (100 * i / (double)n_events) << " %)" << endl;
		}

		if (ch_id == ch_to_process)
		{
			tree_itermediate->GetEntry(i);			
			hist->Fill(num_of_pe_in_event__positive_part_s_int);
			//cout << ch_id << "; " << run_id << "; " << event_id << "; " << num_of_pe_in_event__positive_part_s_int << endl;
		}

	}

	hist->Draw();
}

void Npe_sipm_matrix()
{
	//Npe_sipm_matrix
	TH1F *hist = new TH1F("hist", "hist", 100, 0.1, 600);
	
	ostringstream oss;
	oss << path_name_tree << "hist.txt";
	ofstream file_out(oss.str().c_str());

	tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);

	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);

	const int n_events_in_one_ch = tree_itermediate->GetEntries() / N_ch;

	/*too slow*/
	//for (int i = 0; i < n_events_in_one_ch; i++)
	//{
	//	double n_pe_total = 0;
	//	int index;
	//	for (int j = 0; j < N_ch; j++)
	//	{
	//		index = i + j * n_events_in_one_ch;
	//		chain_all_ch->GetEntry(index);
	//		tree_itermediate->GetEntry(index);
	//
	//		//cout << "index = " << index << endl;
	//
	//		if (index % 1000 == 0)
	//		{
	//			//cout << "event = " << index << " (" << (100 * index / (double)(N_ch*n_events_in_one_ch)) << " %)" << endl;
	//		}
	//		
	//		if (ch_id > 2)
	//		{
	//			n_pe_total += num_of_pe_in_event__positive_part_s_int;
	//		}
	//
	//	}
	//	cout << "INDEX = " << index << endl;
	//	hist->Fill(n_pe_total);			
	//}

	const int n_events_one_ch = n_events_per_file * (run_to - run_from + 1);

	for (int i = 0; i < n_events_one_ch; i++)
	{
		TreeInfoAllCh_tree->GetEntry(i);
		hist->Fill(num_of_pe_in_event_all_ch__positive_part_s_int);
		file_out << num_of_pe_in_event_all_ch__positive_part_s_int << endl;
	}
		

	hist->Draw();
}

void XY_cog()
{
	ostringstream oss;
	oss << path_name_tree << "xy_cog.txt";
	ofstream file_out(oss.str().c_str());

	const int n_events_one_ch = n_events_per_file * (run_to - run_from + 1);

	for (int i = 0; i < n_events_one_ch; i++)
	{
		TreeInfoAllCh_tree->GetEntry(i);
		file_out << x_cog << " " << y_cog << endl;
	}
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
					
		REMEMBER_CUT(ch_id == 38 && run_id == 330 && event_id == 0)
		if (cut_condition_bool)
		{
			cout << "in if (cut_condition_bool)" << endl;
			
			chain_all_ch->SetBranchStatus("data_der", 1);
			chain_all_ch->SetBranchAddress("data_der", &data_der);
			chain_all_ch->SetBranchStatus("data_raw", 1);
			chain_all_ch->SetBranchAddress("data_raw", &data_raw);
			chain_all_ch->SetBranchStatus("data_without_slope", 1);
			chain_all_ch->SetBranchAddress("data_without_slope", &data_without_slope);

			chain_all_ch->GetEntry(i);

			//TGraph *gr = new TGraph(WAVE_ARRAY_COUNT, &time[0], &( TypeConvertion::GetVectorMultiplyToScalar( (*data_der), 1 )  [0]));
			/*TGraph *gr = new TGraph(WAVE_ARRAY_COUNT, &time[0], &((*data_der)[0]));
			gr->SetTitle("data_der");
			gr->SetMarkerStyle(20);
			gr->SetMarkerSize(1);
			gr->SetLineColor(kPink);
			gr->Draw("ALP");*/

			TGraph *gr_3 = new TGraph(WAVE_ARRAY_COUNT, &time[0], &((*data_without_slope)[0]));
			gr_3->SetMarkerStyle(20);
			gr_3->SetMarkerSize(0.5);
			//gr_3->SetMarkerColor(kRed);
			gr_3->SetLineColor(kPink);
			gr_3->SetTitle(cut_condition_srt.c_str());
			gr_3->Draw("ALP");

			/*TGraph *gr_2 = new TGraph(WAVE_ARRAY_COUNT, &time[0], &(TypeConvertion::GetVectorFromScalar(WAVE_ARRAY_COUNT, baseline))[0]);
			gr_2->SetLineColor(kGreen);
			gr_2->Draw("same L");*/


			tree_itermediate->GetEntry(i);			
			COUT((*signals_x_start).size());
			COUT((*signals_x_stop).size());
			COUT((*local_baseline).size());
			COUT((*integral_one_peak).size());
			COUT((*one_peak_y_maximum).size());
			COUT((*num_of_pe_in_one_peak).size());			

			vector<double> signals_x_values;
			vector<double> signals_y_values;
			vector<double> local_baseline_y_values;			
			for (int j = 0; j < (*signals_x_start).size(); j++)
			{
				for (int k = (*signals_x_start)[j]; k < (*signals_x_stop)[j]; k++)
				{
					signals_x_values.push_back(k * HORIZ_INTERVAL);					
					signals_y_values.push_back((*data_without_slope)[k]);
					local_baseline_y_values.push_back((*local_baseline)[j]);					
				}
			}

			if (signals_x_values.size() > 0)
			{
				TGraph *gr_peaks = new TGraph(signals_x_values.size(), &signals_x_values[0], &signals_y_values[0]);
				gr_peaks->SetMarkerSize(1);
				gr_peaks->SetMarkerStyle(29);
				gr_peaks->SetMarkerColor(kBlue);
				gr_peaks->GetXaxis()->SetLimits(0, 160E3);
				gr_peaks->Draw("same P");

				TGraph *gr_local_baseline = new TGraph(signals_x_values.size(), &signals_x_values[0], &local_baseline_y_values[0]);
				gr_local_baseline->SetMarkerSize(1);
				gr_local_baseline->SetMarkerStyle(20);
				gr_local_baseline->SetMarkerColor(kGreen);
				gr_local_baseline->Draw("same P");
			}

			COUT(signals_x_values.size());
			COUT(signals_y_values.size());
			COUT(local_baseline_y_values.size());

			break;
		}
	}
}

void Calibration()
{
	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);

	

	TH1F *h = new TH1F("hist","", 200, 0, 10000);
	
	const int n_events = chain_all_ch->GetEntries();
	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);

		if (i % 1000 == 0 || i == (n_events - 1))
		{
			double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
			cout << "event = " << i << " (" << val << " %)" << endl;
		}

		REMEMBER_CUT(ch_id == 59)
		if (cut_condition_bool)
		{
			tree_itermediate->GetEntry(i);

			for (int j = 0; j < (*integral_one_peak).size(); j++)
			{
				h->Fill((*integral_one_peak)[j]);
			}
			
		}

	}

	//h->GetBinWidth(1);
	h->SetTitle(cut_condition_srt.c_str());
	h->Draw();

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
	tree_info->SetBranchAddress("n_events_per_file", &n_events_per_file);
	tree_info->SetBranchAddress("run_from", &run_from);
	tree_info->SetBranchAddress("run_to", &run_to);

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
	//TreeInfoAllCh
	ostringstream f_TreeInfoAllCh_name;
	f_TreeInfoAllCh_name << path_name_tree << "TreeInfoAllCh.root";

	TFile *f_TreeInfoAllCh = new TFile(f_TreeInfoAllCh_name.str().c_str());
	TreeInfoAllCh_tree = (TTree*)f_TreeInfoAllCh->Get("TreeInfoAllCh");

	TreeInfoAllCh_tree->SetBranchAddress("num_of_pe_in_event_all_ch__positive_part_s_int", &num_of_pe_in_event_all_ch__positive_part_s_int);
	TreeInfoAllCh_tree->SetBranchAddress("x_cog", &x_cog);
	TreeInfoAllCh_tree->SetBranchAddress("y_cog", &y_cog);
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

	COUT(tree_itermediate->GetEntries());
	COUT(chain_all_ch->GetEntries());

	if (tree_itermediate->GetEntries() != chain_all_ch->GetEntries())
	{
		cout << "Sorry, but tree_itermediate->GetEntries() != chain_all_ch->GetEntries(): " << 
			tree_itermediate->GetEntries() << " != " << chain_all_ch->GetEntries() << endl;

		system("pause");
		exit(2);
	}

	//Npe_sipm_matrix();
	Show_individual_signals();
	//Calibration();
	//XY_cog();

	
	
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