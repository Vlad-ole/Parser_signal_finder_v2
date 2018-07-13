//c++
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <algorithm>

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
#include "TypeConvertion.h"
#include "ChCharacteristics.h"
#include "Simple_MC.h"
#include "Singleton.h"
#include "Interpolate2D.h"

using namespace std;
Singleton* Singleton::single = NULL;


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
double min_element_;
double max_element_;
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
double x_by_max;
double y_by_max;
double x_cog_modified;
double y_cog_modified;

//---------------------------------------------

void Correlations()
{
	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);

	ostringstream oss;
	oss << path_name_tree << "Npe_ch_i.txt";
	ofstream file_out_ch_i(oss.str().c_str());

	oss.str("");
	oss << path_name_tree << "Npe_ch_j.txt";
	ofstream file_out_ch_j(oss.str().c_str());

	const int n_events = chain_all_ch->GetEntries();
	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);
		tree_itermediate->GetEntry(i);

		if (i % 1000 == 0 || i == (n_events - 1))
		{
			double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
			cout << "event = " << i << " (" << val << " %)" << endl;
		}

		if (ch_id == 38)
		{
			//cout << "ch 38; " << num_of_pe_in_event__positive_part_s_int << endl;
			file_out_ch_i << num_of_pe_in_event__positive_part_s_int << "\n";
		}
		if (ch_id == 41)
		{
			//cout << "ch 41 " << num_of_pe_in_event__positive_part_s_int << endl;
			file_out_ch_j << num_of_pe_in_event__positive_part_s_int << "\n";
		}

	}
}



double Npe_sipm_one_ch(int ch_to_process, bool is_draw_hist)
{
	//Npe_sipm_matrix
	TH1F *hist = new TH1F("hist", "hist", 100, 0.1, 30);
	//const int ch_to_process = 59;
	COUT(ch_to_process);

	tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);

	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);

	const int n_events = tree_itermediate->GetEntries();
	if (is_draw_hist)
	{
		cout << "tree_itermediate->GetEntries() = " << n_events << endl;
		cout << "chain_all_ch->GetEntries() = " << chain_all_ch->GetEntries() << endl;
	}
	

	chain_all_ch->GetEntry(0);
	if (is_draw_hist)
	{
		cout << ch_id << "; " << run_id << "; " << event_id << "; " << num_of_pe_in_event__positive_part_s_int << endl;
	}
	

	const int n_events_in_one_ch = tree_itermediate->GetEntries() / N_ch;
	vector<bool> cut_is_good;
	cut_is_good.resize(n_events_in_one_ch);
	
	//check 3PMT amplitude for cuts
	for (int i = 0; i < n_events_in_one_ch; i++)
	{
		//chain_all_ch->GetEntry(i);
		tree_itermediate->GetEntry(i);
		double N_pe_3PMT = num_of_pe_in_event__positive_part_s_int * 1E-12 * pow(10, (12.0 / 20.0)) / 2.1325E-8;
		//COUT(N_pe_3PMT);
		bool cut = (max_element_ < 900) && (min_element_ > -900);
		//cut = N_pe_3PMT > 145 && N_pe_3PMT < 285
		if (cut)//------------------ IMPORTANT ----------------------------------//
		{
			cut_is_good[i] = true;
		}
	}

	int internal_counter = 0;
	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);
		
		if (is_draw_hist)
		{
			if (i % 10000 == 0)
			{
				cout << "event = " << i << " (" << (100 * i / (double)n_events) << " %)" << endl;
			}
		}
		
		if (ch_id == ch_to_process)
		{
			tree_itermediate->GetEntry(i);
			if (cut_is_good[internal_counter])
			{
				hist->Fill(num_of_pe_in_event__positive_part_s_int);
			}			
			internal_counter++;
			//cout << ch_id << "; " << run_id << "; " << event_id << "; " << num_of_pe_in_event__positive_part_s_int << endl;
		}

	}

	//COUT(internal_counter);
	//COUT(n_events_in_one_ch);

	double result = hist->GetMean();

	if (is_draw_hist)
	{
		hist->Draw();
	}
	else
	{
		delete hist;
	}
	


	return result;
}


void Npe_sipm_one_ch_loop()
{
	//for (int i = 0; i < /*28*/ 2; i++)
	//{
	//	cout << i << "\t" << GetChIdSiPMCorrect(i) << "\t" << (Npe_sipm_one_ch(GetChIdSiPMCorrect(i), true)) << endl;
	//}
	
	string file_out_s = path_name_tree + "xy_cog_avr.txt";
	ofstream file_out(file_out_s.c_str());

	bool is_drar_hist = false;

	
	//-----------------------
	double N_pe_56 = Npe_sipm_one_ch(56, is_drar_hist);
	double N_pe_57 = Npe_sipm_one_ch(57, is_drar_hist);
	double N_pe_59 = Npe_sipm_one_ch(59, is_drar_hist);
	double N_pe_44 = (N_pe_59 + N_pe_57 + N_pe_56 / sqrt(2)) / 3.0;
	//n_pe[44 - 32] = (n_pe[59 - 32] + n_pe[57 - 32] + n_pe[56 - 32] / sqrt(2)) / 3.0;

	//row1
	file_out << Npe_sipm_one_ch(32, is_drar_hist) /*ch32*/ << "\t" << Npe_sipm_one_ch(33, is_drar_hist)  /*ch33*/ << "\t" << Npe_sipm_one_ch(48, is_drar_hist)  /*ch48*/ << "\t" << Npe_sipm_one_ch(49, is_drar_hist)  /*ch49*/ << "\t" << Npe_sipm_one_ch(34, is_drar_hist)  /*ch34*/ << endl;

	//row2
	file_out << Npe_sipm_one_ch(35, is_drar_hist) /*ch35*/ << "\t" << Npe_sipm_one_ch(50, is_drar_hist)  /*ch50*/ << "\t" << Npe_sipm_one_ch(51, is_drar_hist)  /*ch51*/ << "\t" << Npe_sipm_one_ch(36, is_drar_hist)  /*ch36*/ << "\t" << Npe_sipm_one_ch(37, is_drar_hist)  /*ch37*/ << endl;

	//row3
	file_out << Npe_sipm_one_ch(52, is_drar_hist) /*ch52*/ << "\t" << Npe_sipm_one_ch(53, is_drar_hist)  /*ch53*/ << "\t" << Npe_sipm_one_ch(38, is_drar_hist)  /*ch38*/ << "\t" << Npe_sipm_one_ch(39, is_drar_hist)  /*ch39*/ << "\t" << Npe_sipm_one_ch(54, is_drar_hist)  /*ch54*/ << endl;

	//row4
	file_out << Npe_sipm_one_ch(55, is_drar_hist) /*ch55*/ << "\t" << Npe_sipm_one_ch(40, is_drar_hist)  /*ch40*/ << "\t" << Npe_sipm_one_ch(41, is_drar_hist)  /*ch41*/ << "\t" << N_pe_56  /*ch56*/ << "\t" << N_pe_57  /*ch57*/ << endl;

	//row5
	file_out << Npe_sipm_one_ch(42, is_drar_hist) /*ch42*/ << "\t" << Npe_sipm_one_ch(43, is_drar_hist)  /*ch43*/ << "\t" << Npe_sipm_one_ch(58, is_drar_hist)  /*ch58*/ << "\t" << N_pe_59  /*ch59*/ << "\t" << N_pe_44  /*ch44*/ << endl;
	//-----------------------
}

void Npe_sipm_matrix()
{
	//Npe_sipm_matrix
	TH1F *hist = new TH1F("hist", "hist", 100, 0, 600);

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

void Npe_sipm_matrix_cuts()
{
	//Npe_sipm_matrix
	TH1F *hist = new TH1F("hist", "hist", 1000, 0, 1500);

	ostringstream oss;
	oss << path_name_tree << "hist.txt";
	ofstream file_out(oss.str().c_str());

	tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);

	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);
	chain_all_ch->SetBranchStatus("min_element", 1);
	chain_all_ch->SetBranchStatus("max_element", 1);

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
	COUT(n_events_one_ch);
	COUT(N_ch);

	for (int i = 0; i < n_events_one_ch; i++)
	{
		TreeInfoAllCh_tree->GetEntry(i);
		const int index = i;
		//COUT(index);
		tree_itermediate->GetEntry(index);
		chain_all_ch->GetEntry(index);

		double dB = 12;
		double SPE = 2.1325E-8;//3PMT 750V
		//double SPE = 8.80454E-9;//3PMT 700V
		//double SPE = 3.314E-9;//3PMT 650V
		//double SPE = 3.55935E-10;//3PMT 550V
		double N_pe_3PMT = num_of_pe_in_event__positive_part_s_int * 1E-12 * pow(10, (dB / 20.0)) / SPE;
		double N_pe_total_SiPM = num_of_pe_in_event_all_ch__positive_part_s_int;

		
		//if (N_pe_3PMT > 100 /*145*/ && N_pe_3PMT < /*285*/ 330 && N_pe_total_SiPM > 0.1 /*(max_element_ < 900) && (min_element_ > -900)*/  /*true*/)
		bool cut_no_saturation = (max_element_ < 900) && (min_element_ > -900);
		bool cut_energy_cut = N_pe_3PMT > 100 && N_pe_3PMT < 330;
		//bool cut_rectangle_cut = (N_pe_3PMT > 200 && N_pe_3PMT < 250) && (N_pe_total_SiPM > 40 && N_pe_total_SiPM < 100);
		//bool cut_SiPM_N_pe_total_th = N_pe_total_SiPM > 0.1 /*0.1*/;
		bool cut_SiPM_N_pe_region = N_pe_total_SiPM > 90 && N_pe_total_SiPM < 310;

		bool Npe_th_low = N_pe_total_SiPM > 100;
		bool Npe_th_high = N_pe_total_SiPM < 300;

		if (/*true*/ cut_no_saturation && cut_SiPM_N_pe_region /*&& cut_energy_cut*/ /*&& Npe_th_low*/ /*&& Npe_th_high*/)
		{
			//double val = N_pe_total_SiPM;
			//double val = N_pe_3PMT;
			//hist->Fill(val);
			//file_out << val << endl;
			//file_out << N_pe_3PMT << " " << N_pe_total_SiPM << endl;
			file_out << x_cog << " " << y_cog << endl;
			//file_out << x_by_max << " " << y_by_max << endl;
			//file_out << x_cog_modified << " " << y_cog_modified << endl;
			//file_out << x_cog << " " << y_cog << " " << x_by_max << " " << y_by_max << endl;
			//file_out << N_pe_total_SiPM << endl;
		}


	}


	hist->Draw();
}

TGraph2D* Experimental_distribution_xy()
{
	//Npe_sipm_matrix

	ostringstream oss;
	oss << path_name_tree << "hist.txt";
	ofstream file_out(oss.str().c_str());

	tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);

	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);
	chain_all_ch->SetBranchStatus("min_element", 1);
	chain_all_ch->SetBranchStatus("max_element", 1);

	const int n_events = tree_itermediate->GetEntries();
	const int n_events_in_one_ch = tree_itermediate->GetEntries() / N_ch;

	const int n_events_one_ch = n_events_per_file * (run_to - run_from + 1);
	COUT(n_events_one_ch);
	COUT(N_ch);

	vector<bool> is_good;
	int N_good = 0;
	is_good.resize(n_events_one_ch);

	for (int i = 0; i < n_events_one_ch; i++)
	{
		TreeInfoAllCh_tree->GetEntry(i);
		const int index = i;
		//COUT(index);
		tree_itermediate->GetEntry(index);
		chain_all_ch->GetEntry(index);

		double N_pe_3PMT = num_of_pe_in_event__positive_part_s_int * 1E-12 * pow(10, (12.0 / 20.0)) / 2.1325E-8;
		double N_pe_total_SiPM = num_of_pe_in_event_all_ch__positive_part_s_int;

		bool no_saturation_cut = (max_element_ < 900) && (min_element_ > -900);
		//cut = N_pe_3PMT > 145 && N_pe_3PMT < 285 && N_pe_total_SiPM > 0.1 && x_by_max == 0 && y_by_max == 0;
		//bool energy_cut = N_pe_3PMT > 100 && N_pe_3PMT < 410;//<--------------------------------------------------------------------------
		bool Npe_th_low = N_pe_total_SiPM > /*0.1*/ 100;
		bool Npe_th_high = N_pe_total_SiPM < 10000;
		bool energy_cut = (70 < N_pe_3PMT) && (N_pe_3PMT < 85);
		if (no_saturation_cut && x_by_max == 0 && y_by_max == 0 /*&& energy_cut*/ && Npe_th_low && Npe_th_high)
		{
			is_good[i] = true;
			N_good++;
		}
	}

	cout << "N_events after cut = " << N_good << endl;

	vector<double> n_pe;
	vector<double> n_pe_raw;
	n_pe.resize(25);
	n_pe_raw.resize(25);
	int internal_counter = 0;
	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);

		if (true)
		{
			if (i % 10000 == 0)
			{
				cout << "event = " << i << " (" << (100 * i / (double)n_events) << " %)" << endl;
			}
		}

		int event_index = i % n_events_one_ch;
		if (ch_id >= 32 && is_good[event_index])
		{
			tree_itermediate->GetEntry(i);
			TreeInfoAllCh_tree->GetEntry(event_index);

			//for xy distribution shape
			n_pe[GetArrayPositionSiPM(ch_id)] += (num_of_pe_in_event__positive_part_s_int / num_of_pe_in_event_all_ch__positive_part_s_int);

			//for amplitude info
			//n_pe[GetArrayPositionSiPM(ch_id)] += (num_of_pe_in_event__positive_part_s_int / N_good);
			n_pe_raw[GetArrayPositionSiPM(ch_id)] += num_of_pe_in_event__positive_part_s_int;
		}
	}

	//real distribution with proper xy and amp
	double n_pe_max = *std::max_element(n_pe.begin(), n_pe.end());
	for (int i = 0; i < n_pe.size(); i++)
	{
		n_pe[i] = n_pe[i] * (n_pe_raw[GetArrayPositionSiPM(38)] / n_pe_max) / N_good;
	}

	//-----------------------
	n_pe[GetArrayPositionSiPM(44)] = (n_pe[GetArrayPositionSiPM(59)] + n_pe[GetArrayPositionSiPM(57)] + n_pe[GetArrayPositionSiPM(56)] / sqrt(2)) / 3.0;

	//row1
	file_out << n_pe[GetArrayPositionSiPM(32)] /*ch32*/ << "\t" << n_pe[GetArrayPositionSiPM(33)]  /*ch33*/ << "\t" << n_pe[GetArrayPositionSiPM(48)]  /*ch48*/ << "\t" << n_pe[GetArrayPositionSiPM(49)]  /*ch49*/ << "\t" << n_pe[GetArrayPositionSiPM(34)]  /*ch34*/ << endl;

	//row2
	file_out << n_pe[GetArrayPositionSiPM(35)] /*ch35*/ << "\t" << n_pe[GetArrayPositionSiPM(50)]  /*ch50*/ << "\t" << n_pe[GetArrayPositionSiPM(51)]  /*ch51*/ << "\t" << n_pe[GetArrayPositionSiPM(36)]  /*ch36*/ << "\t" << n_pe[GetArrayPositionSiPM(37)]  /*ch37*/ << endl;

	//row3
	file_out << n_pe[GetArrayPositionSiPM(52)] /*ch52*/ << "\t" << n_pe[GetArrayPositionSiPM(53)]  /*ch53*/ << "\t" << n_pe[GetArrayPositionSiPM(38)]  /*ch38*/ << "\t" << n_pe[GetArrayPositionSiPM(39)]  /*ch39*/ << "\t" << n_pe[GetArrayPositionSiPM(54)]  /*ch54*/ << endl;

	//row4
	file_out << n_pe[GetArrayPositionSiPM(55)] /*ch55*/ << "\t" << n_pe[GetArrayPositionSiPM(40)]  /*ch40*/ << "\t" << n_pe[GetArrayPositionSiPM(41)]  /*ch41*/ << "\t" << n_pe[GetArrayPositionSiPM(56)]  /*ch56*/ << "\t" << n_pe[GetArrayPositionSiPM(57)]  /*ch57*/ << endl;

	//row5
	file_out << n_pe[GetArrayPositionSiPM(42)] /*ch42*/ << "\t" << n_pe[GetArrayPositionSiPM(43)]  /*ch43*/ << "\t" << n_pe[GetArrayPositionSiPM(58)]  /*ch58*/ << "\t" << n_pe[GetArrayPositionSiPM(59)]  /*ch59*/ << "\t" << n_pe[GetArrayPositionSiPM(44)]  /*ch44*/ << endl;
	//-----------------------
	
	
	
	//interpolation
	vector<double> x_position;
	vector<double> y_position;
	vector<double> n_pe_corrected;

	const int n_x_SiPM = 5;
	const int y_x_SiPM = 5;
	int N_ch = n_x_SiPM * y_x_SiPM;
	double x_pos = 0;
	double y_pos = 0;
	double step = 10;
	/*for (int i = 0; i < N_ch; i++)
	{
		x_pos = (i % n_x_SiPM - 2) * step;
		y_pos = (i / y_x_SiPM - 2) * step;

		x_position.push_back(x_pos);
		y_position.push_back(y_pos);
		cout << x_position[i] << "\t" << y_position[i] << "\t" << n_pe[i] << endl;
	}*/

	for (int i = 0; i < N_ch; i++)
	{
		int ch = GetChIdSiPMCorrect(i);

		for (int j = 0; j < ChCharacteristics::GetChCharacteristics().size(); j++)
		{
			if (ChCharacteristics::GetChCharacteristics()[j].ch_id == ch)
			{
				x_position.push_back(ChCharacteristics::GetChCharacteristics()[j].x_position);
				y_position.push_back(ChCharacteristics::GetChCharacteristics()[j].y_position);
				n_pe_corrected.push_back(n_pe[i]);
				break;
			}
		}
	}

	
	//additional ch for proper extrapolation
	{
		int step_multiplier = 5;
		
		//
		x_position.push_back(-step_multiplier*step);
		y_position.push_back(-step_multiplier * step);
		n_pe_corrected.push_back(0);
		//
		x_position.push_back(0);
		y_position.push_back(-step_multiplier * step);
		n_pe_corrected.push_back(0);
		//
		x_position.push_back(step_multiplier * step);
		y_position.push_back(-step_multiplier * step);
		n_pe_corrected.push_back(0);


		//
		x_position.push_back(-step_multiplier * step);
		y_position.push_back(0);
		n_pe_corrected.push_back(0);
		//
		x_position.push_back(step_multiplier * step);
		y_position.push_back(0);
		n_pe_corrected.push_back(0);


		//
		x_position.push_back(-step_multiplier * step);
		y_position.push_back(step_multiplier * step);
		n_pe_corrected.push_back(0);
		//
		x_position.push_back(0);
		y_position.push_back(step_multiplier * step);
		n_pe_corrected.push_back(0);
		//
		x_position.push_back(step_multiplier * step);
		y_position.push_back(step_multiplier * step);
		n_pe_corrected.push_back(0);

		N_ch += 8;
	}

	{
		double val = 0.05 * n_pe[GetArrayPositionSiPM(38)];
		int step_multiplier = 4;
		for (int i = -4; i <= 4; i++)
		{
			x_position.push_back(i * step);
			y_position.push_back(-step_multiplier * step);
			n_pe_corrected.push_back(val);
			N_ch++;
		}

		for (int i = -4; i <= 4; i++)
		{
			x_position.push_back(i * step);
			y_position.push_back(step_multiplier * step);
			n_pe_corrected.push_back(val);
			N_ch++;
		}

		for (int i = -3; i <= 3; i++)
		{
			x_position.push_back(-step_multiplier * step);
			y_position.push_back(i * step);
			n_pe_corrected.push_back(val);
			N_ch++;
		}

		for (int i = -3; i <= 3; i++)
		{
			x_position.push_back(step_multiplier * step);
			y_position.push_back(i * step);
			n_pe_corrected.push_back(val);
			N_ch++;
		}
	}

	TGraph2D* gr2D = new TGraph2D(N_ch, &x_position[0], &y_position[0], &n_pe_corrected[0]);
	gr2D->SetNpx(500);
	gr2D->SetNpy(500);
	//TH2D *h_tmp = new TH2D("h2", "h2", 1000, -50, 50, 1000, -50, 50);
	//gr2D->Interpolate();
	g()->c->cd(1);	
	//gr2D->SetHistogram(h_tmp);
	//gr2D->Draw("TRI1");

	//fix root bug "TGraph2D interpolation problem"
	//https://root-forum.cern.ch/t/tgraph2d-interpolation-problem/17807
	TH2D *h_tmp = new TH2D("h2", "h2", 1000, -55, 55, 1000, -55, 55);
	h_tmp = gr2D->GetHistogram(); 
	h_tmp->Draw("TRI1");

	////test
	//for (int i_tmp = -50; i_tmp < 50; i_tmp++)
	//{
	//	//cout << i_tmp << "; z = " << gr2D->Interpolate(i_tmp, -20) << endl;
	//	cout << i_tmp << "; z = " << h_tmp->Interpolate(i_tmp, 20) << endl;
	//}
	////double n_pe_tmp = gr2D->Interpolate(0, 0);

	vector<double> x_test;
	vector<double> y_test;
	vector<double> n_pe_test;

	/*test of interpolation*/
	for (int i = -50; i < 50; i++)
	{
		double x = i;
		double y = 10;
		x_test.push_back(x);
		y_test.push_back(y);
		n_pe_test.push_back(h_tmp->Interpolate(x, y));
	}
	TGraph2D* gr2D_points = new TGraph2D(x_test.size(), &x_test[0], &y_test[0], &n_pe_test[0]);
	gr2D_points->Draw("same p0");



	return gr2D;
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

		REMEMBER_CUT(ch_id == 38 && run_id == 355 && event_id == 500)
			if (cut_condition_bool && ch_id > 2)
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

				for (int k = 0; k < (*integral_one_peak).size(); k++)
				{
					cout << (*signals_x_start)[k] << "; " << (*signals_x_stop)[k] << "; " << (*integral_one_peak)[k] << endl;
				}

				break;
			}
			else if (cut_condition_bool && ch_id <= 2)
			{
				chain_all_ch->SetBranchStatus("data_raw", 1);
				chain_all_ch->SetBranchAddress("data_raw", &data_raw);
				chain_all_ch->GetEntry(i);

				TGraph *gr_3 = new TGraph(WAVE_ARRAY_COUNT, &time[0], &((*data_raw)[0]));
				gr_3->SetMarkerStyle(20);
				gr_3->SetMarkerSize(0.5);
				//gr_3->SetMarkerColor(kRed);
				gr_3->SetLineColor(kPink);
				gr_3->SetTitle(cut_condition_srt.c_str());
				gr_3->Draw("ALP");

				break;
			}
	}
}

void Show_individual_signals_in_3d()
{
	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);
	chain_all_ch->SetBranchStatus("max_element", 1);
	chain_all_ch->SetBranchStatus("min_element", 1);

	const int n_events = chain_all_ch->GetEntries();

	vector<double> n_pe;
	const int n_pe_size = /*32*/ 28;//60, 61, 62, 63 are inactive, so 28 is enough
	n_pe.resize(n_pe_size);

	int your_run_id = 204;
	int your_event_id = 507;
	bool cut_is_ok = false;

	const int n_events_one_ch = n_events_per_file * (run_to - run_from + 1);
	for (int i = 0; i < n_events_one_ch; i++)
	{
		chain_all_ch->GetEntry(i);		

		if (i % 10000 == 0 || i == (n_events - 1))
		{
			double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
			cout << "event = " << i << " (" << val << " %)" << endl;
		}

		if (run_id == your_run_id && event_id == your_event_id)
		{
			tree_itermediate->GetEntry(i);
			double N_pe_3PMT = num_of_pe_in_event__positive_part_s_int * 1E-12 * pow(10, (12.0 / 20.0)) / 2.1325E-8;
			bool cut = (max_element_ < 900) && (min_element_ > -900) /*&& (num_of_pe_in_event_all_ch__positive_part_s_int > 0)*/;
			//cut = N_pe_3PMT > 145 && N_pe_3PMT < 285;
			if (cut) //-------------------* important! * ---------------------------------------------//
			{
				cut_is_ok = true;
			}	

			TreeInfoAllCh_tree->GetEntry(i);
			ostringstream oss;
			oss << path_name_tree << "xy_one_event.txt";
			ofstream file_out(oss.str().c_str());
			file_out << "x_cog = " << x_cog << endl <<
						"y_cog = " << y_cog << endl <<
						"x_by_max = " << x_by_max << endl <<
						"y_by_max = " << y_by_max << endl << 
						"x_cog_modified = " << x_cog_modified << endl <<
						"y_cog_modified = " << y_cog_modified << endl ;
			//system("pause");

			break;			
		}
		if (i == (n_events_one_ch - 1))
		{
			cout << "Error: there are no such combination of (run_id && event_id)" << endl;
		}		
	}


	if (cut_is_ok)
	{
		cout << "run_id = " << your_run_id << " and event_id = " << your_event_id <<
			" inside range" << endl;
		
		for (int m = 0; m < n_pe_size; m++)
		{
			cout << "ch = " << GetChIdSiPM(m) << endl;

			for (int i = 0; i < n_events; i++)
			{
				chain_all_ch->GetEntry(i);

				//if (i % 50000 == 0 || i == (n_events - 1))
				//{
				//	double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
				//	cout << "event = " << i << " (" << val << " %)" << endl;
				//	cout << "ch_id = " << ch_id << "; GetChIdSiPM(m) = " << GetChIdSiPM(m) << endl;
				//}			

				if (ch_id == GetChIdSiPM(m) && run_id == your_run_id && event_id == your_event_id)
				{
					tree_itermediate->GetEntry(i);
					n_pe[m] = num_of_pe_in_event__positive_part_s_int;
					break;
				}

				if (i == (n_events - 1))
				{
					cout << "There are no such combination of (ch_id,run_id,event_id)" << endl;
				}
			}
		}

		string file_out_s = path_name_tree + "xy_cog_event.txt";
		ofstream file_out(file_out_s.c_str());

		//-----------------------
		n_pe[44 - 32] = (n_pe[59 - 32] + n_pe[57 - 32] + n_pe[56 - 32] / sqrt(2)) / 3.0;

		//row1
		file_out << n_pe[32 - 32] /*ch32*/ << "\t" << n_pe[33 - 32]  /*ch33*/ << "\t" << n_pe[48 - 32]  /*ch48*/ << "\t" << n_pe[49 - 32]  /*ch49*/ << "\t" << n_pe[34 - 32]  /*ch34*/ << endl;

		//row2
		file_out << n_pe[35 - 32] /*ch35*/ << "\t" << n_pe[50 - 32]  /*ch50*/ << "\t" << n_pe[51 - 32]  /*ch51*/ << "\t" << n_pe[36 - 32]  /*ch36*/ << "\t" << n_pe[37 - 32]  /*ch37*/ << endl;

		//row3
		file_out << n_pe[52 - 32] /*ch52*/ << "\t" << n_pe[53 - 32]  /*ch53*/ << "\t" << n_pe[38 - 32]  /*ch38*/ << "\t" << n_pe[39 - 32]  /*ch39*/ << "\t" << n_pe[54 - 32]  /*ch54*/ << endl;

		//row4
		file_out << n_pe[55 - 32] /*ch55*/ << "\t" << n_pe[40 - 32]  /*ch40*/ << "\t" << n_pe[41 - 32]  /*ch41*/ << "\t" << n_pe[56 - 32]  /*ch56*/ << "\t" << n_pe[57 - 32]  /*ch57*/ << endl;

		//row5
		file_out << n_pe[42 - 32] /*ch42*/ << "\t" << n_pe[43 - 32]  /*ch43*/ << "\t" << n_pe[58 - 32]  /*ch58*/ << "\t" << n_pe[59 - 32]  /*ch59*/ << "\t" << n_pe[44 - 32]  /*ch44*/ << endl;
		//-----------------------
	}
	else
	{
		cout << "Sorry, but this event is out of cuts" << endl;
	}

}

void Calibration()
{
	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);



	TH1F *h = new TH1F("hist", "", 1500, 0, 50000);

	const int n_events = chain_all_ch->GetEntries();
	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);

		if (i % 1000 == 0 || i == (n_events - 1))
		{
			double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
			cout << "event = " << i << " (" << val << " %)" << endl;
		}

		REMEMBER_CUT(ch_id == 33)
			if (cut_condition_bool)
			{
				tree_itermediate->GetEntry(i);

				for (int j = 0; j < (*integral_one_peak).size(); j++)
				{
					//h->Fill((*integral_one_peak)[j]);
					h->Fill((*integral_one_peak)[j]);
				}

			}

	}

	//h->GetBinWidth(1);
	h->SetTitle(cut_condition_srt.c_str());
	h->Draw();

}

void TimeSpectrum()
{
	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);

	vector<double> time_position;
	vector<double> n_pe_in_peak;

	const int n_events = chain_all_ch->GetEntries();
	const int n_events_one_ch = n_events_per_file * (run_to - run_from + 1);

	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);
		tree_itermediate->GetEntry(i);		
		TreeInfoAllCh_tree->GetEntry(i % n_events_one_ch);

		if (i % 1000 == 0 || i == (n_events - 1))
		{
			double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
			cout << "event = " << i << " (" << val << " %)" << endl;
		}

		if (ch_id > 2)
		{
			for (int j = 0; j < (*signals_x_start).size(); j++)
			{
				double N_pe_total_SiPM = num_of_pe_in_event_all_ch__positive_part_s_int;
				bool cut_integral_one_peak = (*integral_one_peak)[j] > 1000;
				bool cut_num_of_pe = N_pe_total_SiPM > 100 && N_pe_total_SiPM < 200;
				if (cut_integral_one_peak /*&& cut_num_of_pe*/)
				{
					time_position.push_back(HORIZ_INTERVAL * ((*signals_x_start)[j] + (*signals_x_stop)[j]) / 2.0);
					//n_pe_in_peak.push_back((*num_of_pe_in_one_peak)[j]);
					n_pe_in_peak.push_back((*integral_one_peak)[j]);
					//cout << time_position[j] << "; " << n_pe_in_peak[j] << endl;
				}

			}
		}

	}


	TH2F *hist2 = new TH2F("h2", "Time spectrum: SiPM-matrix all ch", 160, 0, 160E3, 1000, 0, 50000);
	for (int i = 0; i < time_position.size(); i++)
	{
		hist2->Fill(time_position[i], n_pe_in_peak[i]/*, n_pe_in_peak[i]*/);
	}
	//hist2->Draw();
	TH1D * projh2X = hist2->ProjectionX();
	//projh2X->Draw();

	TGraph *gr = new TGraph(time_position.size(), &time_position[0], &n_pe_in_peak[0]);
	gr->Draw("AP");

}

void Npe_PMT()
{

	ostringstream oss;
	oss << path_name_tree << "Npe_pmt.txt";
	ofstream file_out(oss.str().c_str());

	TH1F *hist = new TH1F("hist", "hist", 100, -50E3, 10000E3);
	const int ch_to_process = 0;
	//const int array_position = GetArrayPosition(ch_to_process);

	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("min_element", 1);
	chain_all_ch->SetBranchStatus("max_element", 1);

	tree_itermediate->SetBranchStatus("*", 0); //disable all branches
	tree_itermediate->SetBranchStatus("num_of_pe_in_event__positive_part_s_int", 1);


	const int n_events = tree_itermediate->GetEntries();
	cout << " = " << n_events << endl;

	for (int i = 0; i < n_events; i++)
	{
		double val = 0;

		chain_all_ch->GetEntry(i);
		tree_itermediate->GetEntry(i);

		if (i % 1000 == 0)
		{
			cout << "event = " << i << " (" << (100 * i / (double)n_events) << " %)" << endl;
		}

		if (ch_id == ch_to_process && (max_element_ < 900) && (min_element_ > -900))
		{
			const int calib_const = 1;
			const double val = num_of_pe_in_event__positive_part_s_int * calib_const;
			hist->Fill(val);
			file_out << val << endl;
		}

		if (ch_id > ch_to_process)
		{
			break;
		}

	}

	hist->Draw();
}

void AvrSignal()
{
	chain_all_ch->SetBranchStatus("*", 0); //disable all branches
	chain_all_ch->SetBranchStatus("ch_id", 1);
	chain_all_ch->SetBranchStatus("run_id", 1);
	chain_all_ch->SetBranchStatus("event_id", 1);
	chain_all_ch->SetBranchStatus("baseline", 1);
	chain_all_ch->SetBranchStatus("min_element", 1);
	chain_all_ch->SetBranchStatus("max_element", 1);

	const int ch_to_process = 0;
	vector<double> data_raw_average;
	data_raw_average.resize(WAVE_ARRAY_COUNT);

	int cut_pass_counter = 0;
	const int n_events = chain_all_ch->GetEntries();
	for (int i = 0; i < n_events; i++)
	{
		chain_all_ch->GetEntry(i);

		if (i % 1000 == 0 || i == (n_events - 1))
		{
			double val = n_events > 1 ? (100 * i / (double)(n_events - 1)) : 100;
			cout << "event = " << i << " (" << val << " %)" << endl;
		}

		if (ch_id == ch_to_process && (max_element_ < 900) && (min_element_ > -900))
		{
			cut_pass_counter++;
			chain_all_ch->SetBranchStatus("data_raw", 1);
			chain_all_ch->SetBranchAddress("data_raw", &data_raw);
			chain_all_ch->GetEntry(i);

			for (int j = 0; j < WAVE_ARRAY_COUNT; j++)
			{
				data_raw_average[j] += ((*data_raw)[j] - baseline);
			}
		}

		if (ch_id > ch_to_process)
		{
			break;
		}
	}

	for (int j = 0; j < WAVE_ARRAY_COUNT; j++)
	{
		//	data_raw_average[j] = -((data_raw_average[j] / cut_pass_counter) - baseline_average);
		data_raw_average[j] /= cut_pass_counter;
	}
	COUT(cut_pass_counter);

	vector<double> time(WAVE_ARRAY_COUNT);
	for (int i = 0; i < time.size(); i++)
	{
		time[i] = i * HORIZ_INTERVAL;
	}

	TGraph *gr = new TGraph(WAVE_ARRAY_COUNT, &time[0], &data_raw_average[0]);
	gr->SetTitle("Average signal from 3PMT");
	gr->Draw("APL");

	vector<double> baseline(WAVE_ARRAY_COUNT);
	TGraph *gr_baseline = new TGraph(WAVE_ARRAY_COUNT, &time[0], &baseline[0]);
	gr_baseline->Draw("same");

}

int main(int argc, char *argv[])
{
	cout << "\a \a \a \a";

	

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
	TreeInfoAllCh_tree->SetBranchAddress("x_by_max", &x_by_max);
	TreeInfoAllCh_tree->SetBranchAddress("y_by_max", &y_by_max);
	TreeInfoAllCh_tree->SetBranchAddress("x_cog_modified", &x_cog_modified);
	TreeInfoAllCh_tree->SetBranchAddress("y_cog_modified", &y_cog_modified);
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

	chain_all_ch->SetBranchAddress("min_element", &min_element_);
	chain_all_ch->SetBranchAddress("max_element", &max_element_);
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

	//Npe_PMT();	
	//Npe_sipm_matrix();

	//Correlations();
	Npe_sipm_matrix_cuts();

	//Show_individual_signals();
	//Show_individual_signals_in_3d();
	//Npe_sipm_one_ch();
	//Npe_sipm_one_ch_loop();
	//Experimental_distribution_xy();

	/*Simple_MC sim_mc(Experimental_distribution_xy(), false, 1000);
	sim_mc.Calc_center_shift();
	sim_mc.Calc_MC();*/

	//Interpolate2D interpol2d;
	//interpol2d.GetValueBicubic(0, 0);


	//Calibration();
	//XY_cog();
	//TimeSpectrum();
	
	//AvrSignal();


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