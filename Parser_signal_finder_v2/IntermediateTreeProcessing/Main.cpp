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
#include "TChain.h"
#include "TH1F.h"
#include "TSystem.h"
#include "TGraph.h"

//my
#include "RunDescription.h"
#include "IntermediateTreeInfo.h"
#include "PeakFinderFind.h"
#include "ChCharacteristics.h"
#include "TreeInfoAllCh.h"
#include "CoGBase.h"
#include "CalcIntegral.h"

using namespace std;

int main(int argc, char *argv[])
{
	TStopwatch timer_total;
	timer_total.Start();

	bool is_test = false;

	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);

	//---------------------------------------------
	//braches info for tree_raw
	std::vector<double> *data_raw = 0;
	std::vector<double> *data_der = 0;
	std::vector<double> *data_without_slope = 0;
	double min_element;
	double max_element;
	double baseline;
	//---------------------------------------------




	//---------------------------------------------
	//tree_info
	double HORIZ_INTERVAL; //in ns
	int WAVE_ARRAY_COUNT;
	int runs_per_tree_file;
	int N_ch;
	int n_blocks;
	int n_events_per_file;
	int run_from;
	int run_to;

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


	const int n_ch_sipm = 25;

	//Yes, it will take too many RAM. But how to write better?
	int n_events_one_ch;
	if (!is_test)
	{
		n_events_one_ch = n_events_per_file * (run_to - run_from + 1);
	}
	else
	{
		n_events_one_ch = 1;	//test 
	}
	
	
	vector< vector<double> > num_of_pe_in_event_all_ch__positive_part_s_int;
	num_of_pe_in_event_all_ch__positive_part_s_int.resize(n_ch_sipm);
	for (int i = 0; i < n_ch_sipm; i++)
	{
		num_of_pe_in_event_all_ch__positive_part_s_int[i].resize(n_events_one_ch);
	}

	

	ostringstream f_tree_intermediate_name;
	f_tree_intermediate_name << path_name_tree << "tree_intermediate.root";
	cout << f_tree_intermediate_name.str().c_str() << endl;
	TFile* f_tree_intermediate = TFile::Open(f_tree_intermediate_name.str().c_str(), "RECREATE");
	IntermediateTreeInfo tree_intermediate_obj;



	int n_events;
	//loop by chs
	for (int i = 0; i < N_ch; i++)
	{
		if (is_test)
		{
			//test
			n_events = 1;
			n_blocks = 1;
		}		

		TChain chain("tree_raw");
		for (int counter_f_tree = 0; counter_f_tree < n_blocks; counter_f_tree++)
		{
			ostringstream f_tree_name;
			f_tree_name << path_name_tree << "ch_" << GetChId(i) << "__block_" << setfill('0') << setw(7) << counter_f_tree << ".root";
			chain.Add(f_tree_name.str().c_str());
		}
		if (!is_test)
		{
			n_events = chain.GetEntries();
		}

		cout << "i = " << i << "; ch_id = " << GetChId(i) << "; GetEntries = " << n_events << endl;


		//-----------------------------------
		//SetBranchAddress
		chain.SetBranchAddress("data_raw", &data_raw);
		chain.SetBranchAddress("data_der", &data_der);
		chain.SetBranchAddress("data_without_slope", &data_without_slope);

		chain.SetBranchAddress("min_element", &min_element);
		chain.SetBranchAddress("max_element", &max_element);
		chain.SetBranchAddress("baseline", &baseline);
		//-----------------------------------



		//loop by events
		for (int temp_event_id = 0; temp_event_id < n_events; temp_event_id++)
		{
			chain.GetEntry(temp_event_id);

			if (temp_event_id % 100 == 0 || temp_event_id == (n_events - 1))
			{
				double val = n_events > 1 ? (100 * temp_event_id / (double)(n_events - 1)) : 100;
				cout << "ch_id = " << GetChId(i) << "; event = " << temp_event_id << " (" << setprecision(3) << val << " %)" << endl;
			}

			if (GetChId(i) < 3) //process only SiPM ch
			{
				tree_intermediate_obj.signals_x_start.resize(0);
				tree_intermediate_obj.signals_x_stop.resize(0);
				tree_intermediate_obj.local_baseline.resize(0);
				tree_intermediate_obj.one_peak_y_maximum.resize(0);
				tree_intermediate_obj.num_of_pe_in_one_peak.resize(0);
				tree_intermediate_obj.integral_one_peak.resize(0);

				CalcIntegral calc_integral(*data_raw, baseline, 30000, 41700, HORIZ_INTERVAL);
				tree_intermediate_obj.num_of_pe_in_event__positive_part_s_int = 
					calc_integral.GetIntegrtal();
			}
			else
			{
				tree_intermediate_obj.signals_x_start.clear();
				tree_intermediate_obj.signals_x_stop.clear();
				tree_intermediate_obj.local_baseline.clear();
				tree_intermediate_obj.integral_one_peak.clear();
				tree_intermediate_obj.one_peak_y_maximum.clear();
				tree_intermediate_obj.num_of_pe_in_one_peak.clear();

				PeakFinderFind peak_finder_find(*data_without_slope, *data_der, 13 /*this parameter is very important*/, 1 /*this parameter is very important*/, HORIZ_INTERVAL);
				tree_intermediate_obj.local_baseline = peak_finder_find.GetLocalBaselineV();

				//----------------------------------------
				//peak left/right edges
				vector< pair<int, int> > pair_vec = peak_finder_find.GetPeakPositions();
				tree_intermediate_obj.signals_x_start.resize(pair_vec.size());
				tree_intermediate_obj.signals_x_stop.resize(pair_vec.size());
				for (int j = 0; j < pair_vec.size(); j++)
				{
					tree_intermediate_obj.signals_x_start[j] = pair_vec[j].first;
					tree_intermediate_obj.signals_x_stop[j] = pair_vec[j].second;
				}
				//----------------------------------------


				//----------------------------------------
				//caclulate intergal of individual peaks
				double integral_one_event_tmp = 0;
				for (int j = 0; j < pair_vec.size(); j++)
				{
					//choose region (for calib only) 
					//if ((tree_intermediate_obj.signals_x_stop[j] * HORIZ_INTERVAL) > 80000 && (tree_intermediate_obj.signals_x_start[j] * HORIZ_INTERVAL) < 150000)
					{
						double integral_tmp = 0;
						double one_peak_y_maximum_tmp = -1100;
						for (int k = tree_intermediate_obj.signals_x_start[j]; k < tree_intermediate_obj.signals_x_stop[j]; k++)
						{
							double tmp_val = (*data_without_slope)[k] - tree_intermediate_obj.local_baseline[j];
							integral_tmp += tmp_val * HORIZ_INTERVAL;
							if (tmp_val > one_peak_y_maximum_tmp)
								one_peak_y_maximum_tmp = tmp_val;
						}
						tree_intermediate_obj.integral_one_peak.push_back(integral_tmp);
						tree_intermediate_obj.one_peak_y_maximum.push_back(one_peak_y_maximum_tmp);
					}
				}
				//----------------------------------------

				//for sipm
				int point_from = 25000 / HORIZ_INTERVAL;
				int point_to = 55000 / HORIZ_INTERVAL;//it's not so easy to find range of positive part



				//----------------------------------------
				//calc num of pe for one event
				vector<ChCharacteristicsStruct> ch_characteristics_struct = ChCharacteristics::GetChCharacteristics();
				double num_of_pe_in_event__positive_part_s_int_tmp = 0;
				for (int k = 0; k < ch_characteristics_struct.size(); k++)
				{
					if (ch_characteristics_struct[k].ch_id == GetChId(i) && ch_characteristics_struct[k].is_spe_separated_from_noise &&
						ch_characteristics_struct[k].is_physical)
					{
						for (int j = 0; j < tree_intermediate_obj.integral_one_peak.size(); j++)
						{
							//algorithm is not ideal, so I should add some cuts (depend from ch_id)
							if (tree_intermediate_obj.integral_one_peak[j] > ch_characteristics_struct[k].spe_min)
							{
								double n_pe_one_peak_tmp = tree_intermediate_obj.integral_one_peak[j] / ch_characteristics_struct[k].spe_mean;
								tree_intermediate_obj.num_of_pe_in_one_peak.push_back(n_pe_one_peak_tmp);

								if (pair_vec[j].first >= point_from && pair_vec[j].second < point_to)
								{
									num_of_pe_in_event__positive_part_s_int_tmp += n_pe_one_peak_tmp;
								}

							}
						}
					}
				}

				tree_intermediate_obj.num_of_pe_in_event__positive_part_s_int = num_of_pe_in_event__positive_part_s_int_tmp;
				num_of_pe_in_event_all_ch__positive_part_s_int[i - 3][temp_event_id] = num_of_pe_in_event__positive_part_s_int_tmp;
				////----------------------------------------

			}

			tree_intermediate_obj.tree->Fill();

			//break;

		}// end loop by events

		//break;

	}//end loop by chs

	//f_tree_intermediate->cd();
	tree_intermediate_obj.tree->Write();
	f_tree_intermediate->Close();


	//----------------------------------------------------------
	ostringstream f_TreeInfoAllCh_name;
	f_TreeInfoAllCh_name << path_name_tree << "TreeInfoAllCh.root";
	cout << f_TreeInfoAllCh_name.str().c_str() << endl;
	TFile* f_TreeInfoAllCh = TFile::Open(f_TreeInfoAllCh_name.str().c_str(), "RECREATE");
	TreeInfoAllCh TreeInfoAllCh_obj;

	for (int i = 0; i < n_events_one_ch; i++)
	{
		
		vector<double> num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec;
		num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec.resize(n_ch_sipm);

		TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int = 0;
		for (int j = 0; j < n_ch_sipm; j++)
		{
			if (GetChIdSiPM(j) != 44)
			{
				TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
					num_of_pe_in_event_all_ch__positive_part_s_int[j][i];

				num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[j] = num_of_pe_in_event_all_ch__positive_part_s_int[j][i];
			}			
		}

		//add special channels
		//ch 44
		num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(44)] = 
			(num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(59)][i] + 
			num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(57)][i] +
			num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(56)][i] / sqrt(2)) / 3.0;

		TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int += 
			num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(44)];

		CoGBase cog_obj(num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec, false);//by cog or by max
		TreeInfoAllCh_obj.x_cog = cog_obj.GetX();
		TreeInfoAllCh_obj.y_cog = cog_obj.GetY();

		/*cout << "x_cog = " << TreeInfoAllCh_obj.x_cog << endl;
		cout << "y_cog = " << TreeInfoAllCh_obj.y_cog << endl;*/

		TreeInfoAllCh_obj.tree->Fill();
	}	

	f_TreeInfoAllCh->cd();
	TreeInfoAllCh_obj.tree->Write();
	f_TreeInfoAllCh->Close();
	//----------------------------------------------------------


	timer_total.Stop();
	//cout << "n_events = " << n_events << endl;
	cout << "total time = " << timer_total.RealTime() << " sec" << endl;
	cout << "all is ok" << endl;


	system("pause");
	theApp.Terminate();
	theApp.Run();

	return 0;

}