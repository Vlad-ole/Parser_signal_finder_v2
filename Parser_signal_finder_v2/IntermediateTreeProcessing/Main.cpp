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
#include "TypeConvertion.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Press any key to confirm the execution." << endl;
	system("pause");
	
	TStopwatch timer_total;
	timer_total.Start();

	int is_test = 0;
	bool is_recalc_full = true;

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

	TFile *f_tree_info;
	TTree *tree_info;
	f_tree_info = new TFile(f_tree_info_name.str().c_str());
	tree_info = (TTree*)f_tree_info->Get("tree_info");

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
		n_events_one_ch = is_test;	//test 
	}
	
	
	vector< vector<double> > num_of_pe_in_event_all_ch__positive_part_s_int;
	num_of_pe_in_event_all_ch__positive_part_s_int.resize(n_ch_sipm);
	for (int i = 0; i < n_ch_sipm; i++)
	{
		num_of_pe_in_event_all_ch__positive_part_s_int[i].resize(n_events_one_ch);
	}

	TFile* f_tree_intermediate = NULL;
	if (is_recalc_full)
	{
		ostringstream f_tree_intermediate_name;
		f_tree_intermediate_name << path_name_tree << "tree_intermediate.root";
		cout << f_tree_intermediate_name.str().c_str() << endl;
		f_tree_intermediate = TFile::Open(f_tree_intermediate_name.str().c_str(), "RECREATE");		
	}
	IntermediateTreeInfo tree_intermediate_obj;



	int n_events;
	if (is_recalc_full)
	{
		//loop by chs
		for (int i = 0; i < N_ch; i++)
		{
			if (is_test)
			{
				//test
				n_events = is_test;
				n_blocks = 1;//dummy
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
				//test
				//if (GetChId(i) == 36 && temp_event_id == 10341)
				{
					chain.GetEntry(temp_event_id);					
				}
				//continue;

				if (temp_event_id % 100 == 0 || temp_event_id == (n_events - 1))
				{
					double val = n_events > 1 ? (100 * temp_event_id / (double)(n_events - 1)) : 100;
					cout << "ch_id = " << GetChId(i) << "; event = " << temp_event_id << " (" << setprecision(3) << val << " %)" << endl;
				}

				tree_intermediate_obj.signals_x_start.clear();
				tree_intermediate_obj.signals_x_stop.clear();
				tree_intermediate_obj.local_baseline.clear();
				tree_intermediate_obj.integral_one_peak.clear();
				tree_intermediate_obj.one_peak_y_maximum.clear();
				//tree_intermediate_obj.num_of_pe_in_one_peak.clear();

				if (GetChId(i) < 2) //process only PMTs ch
				{
					//continue;
					/*tree_intermediate_obj.signals_x_start.resize(0);
					tree_intermediate_obj.signals_x_stop.resize(0);
					tree_intermediate_obj.local_baseline.resize(0);
					tree_intermediate_obj.one_peak_y_maximum.resize(0);
					tree_intermediate_obj.num_of_pe_in_one_peak.resize(0);
					tree_intermediate_obj.integral_one_peak.resize(0);*/

					tree_intermediate_obj.integral_one_peak.resize(0);


					////for X-ray NBrS
					//CalcIntegral calc_integral(*data_raw, baseline, 32000, 40000, HORIZ_INTERVAL);

					//for Cd
					CalcIntegral calc_integral(*data_raw, baseline, 30000, 41700, HORIZ_INTERVAL);
					
					////for x-ray 20kV
					//CalcIntegral calc_integral(*data_raw, baseline, 35000, 68200, HORIZ_INTERVAL);

					//for x-ray 18kV, 16kV
					//CalcIntegral calc_integral(*data_raw, baseline, 35000, 70000, HORIZ_INTERVAL);

					////for x-ray 14kV
					//CalcIntegral calc_integral(*data_raw, baseline, 35000, 71500, HORIZ_INTERVAL);

					//for x-ray 12kV
					//CalcIntegral calc_integral(*data_raw, baseline, 50000, 74500, HORIZ_INTERVAL);

					////for x-ray 10kV
					//CalcIntegral calc_integral(*data_raw, baseline, 55000, 76000, HORIZ_INTERVAL);

					////for x-ray 8kV
					//CalcIntegral calc_integral(*data_raw, baseline, 55000, 79070, HORIZ_INTERVAL);

					tree_intermediate_obj.num_of_pe_in_event__positive_part_s_int =
						calc_integral.GetIntegrtal();

					PeakFinderFind *peak_finder_find = NULL;
					if (GetChId(i) == 0)
					{
						//PeakFinderFind peak_finder_find(*data_without_slope, *data_der, 20, 2 /*change this*/, HORIZ_INTERVAL, false);//3PMT 800V
						peak_finder_find = new PeakFinderFind(*data_without_slope, *data_der, 20, 2 /*change this*/, HORIZ_INTERVAL, false);//3PMT 800V;
					}
					if (GetChId(i) == 1)
					{
						//PeakFinderFind peak_finder_find(*data_without_slope, *data_der, 20, 4 /*change this*/, HORIZ_INTERVAL, false);//3PMT 800V
						peak_finder_find = new PeakFinderFind(*data_without_slope, *data_der, 20, 4 /*change this*/, HORIZ_INTERVAL, false);//3PMT 800V;
					}

					tree_intermediate_obj.local_baseline = peak_finder_find->GetLocalBaselineV();

					//----------------------------------------
					//peak left/right edges
					vector< pair<int, int> > pair_vec = peak_finder_find->GetPeakPositions();
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

					delete peak_finder_find;

				}
				else if (GetChId(i) >= 32)
				{
					////test
					////-------------

					/*if ((temp_event_id % 10000 == 0) && GetChId(i) == 36)
					{
						int x = 0;
					}

					if ( (temp_event_id % 1000 == 0) && GetChId(i) == 36)
					{
						int x = 0;
					}

					if ((temp_event_id % 100 == 0) && GetChId(i) == 36)
					{
						int x = 0;
					}

					if ((temp_event_id == 10340) && GetChId(i) == 36)
					{
						int x = 0;
					}

					if ((temp_event_id % 10 == 0) && GetChId(i) == 36)
					{
						int x = 0;
					}*/

					////-------------
					
					/*tree_intermediate_obj.signals_x_start.clear();
					tree_intermediate_obj.signals_x_stop.clear();
					tree_intermediate_obj.local_baseline.clear();
					tree_intermediate_obj.integral_one_peak.clear();
					tree_intermediate_obj.one_peak_y_maximum.clear();
					tree_intermediate_obj.num_of_pe_in_one_peak.clear();*/
					tree_intermediate_obj.num_of_pe_in_one_peak.clear();

					//PeakFinderFind peak_finder_find(*data_without_slope, *data_der, 13 /*this parameter is very important*/, 1 /*this parameter is very important*/, HORIZ_INTERVAL);
					//PeakFinderFind peak_finder_find(*data_without_slope, *data_der, 13 /*this parameter is very important*/, 1 /*this parameter is very important*/, HORIZ_INTERVAL);
					//PeakFinderFind peak_finder_find(TypeConvertion::GetVectorMultiplyToScalar(TypeConvertion::GetDifference(*data_raw), -1.0), *data_der, 25 /*this parameter is very important*/, 1 /*change this*/ /*this parameter is very important*/, HORIZ_INTERVAL);//49V
					PeakFinderFind peak_finder_find(*data_without_slope, *data_der, 20, 1 /*change this*/, HORIZ_INTERVAL, true);//49V
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
					//SiPM signal gates


					//for X-ray NBrS
					/*int point_from = 32000 / HORIZ_INTERVAL;
					int point_to = 40000 / HORIZ_INTERVAL;*/

					//for Cd
					//int point_from = 25000 / HORIZ_INTERVAL;
					//int point_to = 55000 / HORIZ_INTERVAL;//it's not so easy to find range of positive part

					////for Cd, 20kV, THGEM 2.2kV
					//int point_from = 25000 / HORIZ_INTERVAL;
					//int point_to = 80000 / HORIZ_INTERVAL;//it's not so easy to find range of positive part

					//for Cd, 20kV, THGEM 2.2kV //standart
					int point_from = 25000 / HORIZ_INTERVAL;
					int point_to = 65000 / HORIZ_INTERVAL;//it's not so easy to find range of positive part

					////for x-ray 20kV, 18, 16, 14
					//int point_from = 40000 / HORIZ_INTERVAL;
					//int point_to = 80000 / HORIZ_INTERVAL;//it's not so easy to find range of positive part

					////for x-ray 12, 10kV
					//int point_from = 45000 / HORIZ_INTERVAL;
					//int point_to = 90000 / HORIZ_INTERVAL;//it's not so easy to find range of positive part

					//////for x-ray 8kV
					//int point_from = 50000 / HORIZ_INTERVAL;
					//int point_to = 100000 / HORIZ_INTERVAL;//it's not so easy to find range of positive part

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

		
	}


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
		
		////case when ch44 is bad
		////-------------------------------------
		//for (int j = 0; j < n_ch_sipm; j++)
		//{
		//	if (GetChIdSiPM(j) != 44)
		//	{
		//		TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
		//			num_of_pe_in_event_all_ch__positive_part_s_int[j][i];

		//		num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[j] = num_of_pe_in_event_all_ch__positive_part_s_int[j][i];
		//	}			
		//}
		////add special channels
		////ch 44
		//num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(44)] = 
		//	(num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(59)][i] + 
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(57)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(56)][i] / sqrt(2)) / 3.0;

		//TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int += 
		//	num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(44)];
		////-------------------------------------


		//case when ch43 && ch44 are bad
		//-------------------------------------
		for (int j = 0; j < n_ch_sipm; j++)
		{
			if (GetChIdSiPM(j) != 43 && GetChIdSiPM(j) != 44)
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
		//-------------------------------------		
		//ch 43
		num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(43)] =
			(num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(40)][i] +
			num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(42)][i] +
			num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(58)][i] ) / 3.0;

		TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
			num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(43)];
		//-------------------------------------




		////case when ch37, ch56, ch43, ch44 are bad
		////-------------------------------------
		//for (int j = 0; j < n_ch_sipm; j++)
		//{
		//	if (GetChIdSiPM(j) != 37 && GetChIdSiPM(j) != 56 && GetChIdSiPM(j) != 43 && GetChIdSiPM(j) != 44)
		//	{
		//		TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
		//			num_of_pe_in_event_all_ch__positive_part_s_int[j][i];

		//		num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[j] = num_of_pe_in_event_all_ch__positive_part_s_int[j][i];
		//	}
		//}
		////add special channels

		////ch37
		//num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(37)] =
		//	(num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(34)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(36)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(54)][i]) / 3.0;
		//TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
		//	num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(37)];

		////ch56
		//num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(56)] =
		//	(num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(39)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(41)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(57)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(59)][i]) / 4.0;
		//TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
		//	num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(56)];

		////ch43
		//num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(43)] =
		//	(num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(40)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(42)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(58)][i]) / 3.0;
		//TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
		//	num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(43)];


		////ch 44
		//num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(44)] =
		//	(num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(59)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(57)][i] +
		//	num_of_pe_in_event_all_ch__positive_part_s_int[GetArrayPositionSiPM(56)][i] / sqrt(2)) / 3.0;
		//TreeInfoAllCh_obj.num_of_pe_in_event_all_ch__positive_part_s_int +=
		//	num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec[GetArrayPositionSiPM(44)];

		//
		////-------------------------------------
		
		
		
		CoGBase cog_obj(num_of_pe_in_event__positive_part_s_int_one_event_one_ch_vec);//by cog and by max
		
		TreeInfoAllCh_obj.x_cog = cog_obj.GetX();
		TreeInfoAllCh_obj.y_cog = cog_obj.GetY();
		
		TreeInfoAllCh_obj.x_by_max = cog_obj.GetXByMax();
		TreeInfoAllCh_obj.y_by_max = cog_obj.GetYByMax();

		TreeInfoAllCh_obj.x_cog_modified = cog_obj.GetXCoGModified();
		TreeInfoAllCh_obj.y_cog_modified = cog_obj.GetYCoGModified();

		//cout << "x_cog = " << TreeInfoAllCh_obj.x_cog << endl;
		//cout << "y_cog = " << TreeInfoAllCh_obj.y_cog << endl;
		//cout << "x_by_max = " << TreeInfoAllCh_obj.x_by_max << endl;
		//cout << "y_by_max = " << TreeInfoAllCh_obj.y_by_max << endl;

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