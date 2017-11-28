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

//my
#include "ReadData_CAEN.h"
#include "RunDescription.h"
#include "TreeInfo.h"
#include  "CalcData.h"

using namespace std;

int main(int argc, char *argv[])
{
	TStopwatch timer_total;	
	timer_total.Start();

	double time_read_binary = 0;
	
	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);	
	
	//-----------------------------------------------------
	comm_info str_comm;
	str_comm.HORIZ_INTERVAL = 16;//ns per point;
	str_comm.WAVE_ARRAY_COUNT = 9999;//number of points in one event

	//tree settings
	const int runs_per_tree_file = 10;

	//which raw files should be processed?
	//this information in RunDescription.cpp
	PathInfo.path_name = PathInfo_path_name;

	const int n_runs = stop_run_number;
	cout << "n_runs = " << stop_run_number - start_run_number + 1 << endl;

	TFile* f_tree = NULL;
	TTree* tree = NULL;	
	//-----------------------------------------------------

		
	//loop by chs
	for (int i = 0; i < n_ch; i++)
	{
		vector<ch_info> ch_list;
		ch_list.resize(1);
		ch_list[0].id = GetChId(i);

		TreeInfo *tree_info_obj = NULL;
		
		//loop by runs
		int counter_f_tree = 0;
		for (int run_number = start_run_number; run_number <= stop_run_number; run_number++)
		{
			//define tree
			if ((run_number - start_run_number) % runs_per_tree_file == 0)
			{
				ostringstream f_tree_name;
				f_tree_name << path_name_tree << "ch_" << GetChId(i) << "__block_" << setfill('0') << setw(7) << counter_f_tree << ".root";
				f_tree = TFile::Open(f_tree_name.str().c_str(), "RECREATE");
				
				tree_info_obj = new TreeInfo();
				tree = tree_info_obj->GetTreePnt();
			}
			
			
			PathInfo.run_number = run_number;
			cout << "i = " << i << "; ch_id = " << GetChId(i) << "; run_number = " << run_number << endl;
			
			TStopwatch timer_read_binary;
			timer_read_binary.Start();
			ReadData_CAEN rdt(PathInfo, ch_list, str_comm);
			timer_read_binary.Stop();
			time_read_binary += timer_read_binary.RealTime();

			//loop by events
			for (int temp_event_id = 0; temp_event_id < PathInfo.events_per_file; temp_event_id++)
			{
				CalcData calc_data(rdt.GetDataDouble()[temp_event_id][0]);
				
				//fill branches
				tree_info_obj->ch_id = GetChId(i);
				tree_info_obj->run_number = run_number;
				tree_info_obj->event_id = temp_event_id;
				
				tree_info_obj->min_element = calc_data.Get_min_element();
				tree_info_obj->max_element = calc_data.Get_max_element();				

				tree_info_obj->data_raw = rdt.GetDataDouble()[temp_event_id][0];
				tree_info_obj->data_der = calc_data.Get_data_der(true);

				tree->Fill();

			}// end loop by events


			if (((run_number - start_run_number) % runs_per_tree_file == runs_per_tree_file - 1) || (run_number == stop_run_number))
			{
				tree->Write();
				f_tree->Close();

				delete f_tree;
				delete tree_info_obj;

				tree_info_obj = NULL;
				f_tree = NULL;
				tree = NULL;

				counter_f_tree++;
			}


		}// end loop by runs
				

	}//end loop by chs


	timer_total.Stop();
	cout << "-------------------------------" << endl;
	cout << "time to read binary files = " << time_read_binary << " sec" << endl;
	cout << " total time = " << timer_total.RealTime() << " sec" << endl;
	cout << "all is ok" << endl;	
	system("pause");
	theApp.Terminate();
	theApp.Run();
	return 0;
}