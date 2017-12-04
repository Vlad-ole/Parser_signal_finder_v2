//c++
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <omp.h> 

//root cern
#include "TApplication.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TTree.h"
#include "TThread.h"

//my
#include "ReadData_CAEN.h"
#include "RunDescription.h"
#include "TreeRaw.h"
#include "CalcData.h"
#include "TreeInfo.h"
#include "TreeRaw.h"

#pragma link C++ class vector<double>
#pragma link C++ class Bool_t
#pragma link C++ class TreeRaw

using namespace std;

int main(int argc, char *argv[])
{
	TStopwatch timer_total;
	timer_total.Start();


	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);

	comm_info str_comm;
	str_comm.HORIZ_INTERVAL = 16;//ns per point;
	str_comm.WAVE_ARRAY_COUNT = 9999;//number of points in one event

	//tree settings
	const int runs_per_tree_file = 10;

	const int n_runs = stop_run_number;
	cout << "n_runs = " << stop_run_number - start_run_number + 1 << endl;

	TThread::Initialize();

#pragma omp parallel for num_threads(4)
	for (int i = 0; i < n_ch; i++)
	{
		vector<ch_info> ch_list;
		ch_list.resize(1);
		ch_list[0].id = GetChId(i);

		path_info PathInfo = { "", 0, /*1000*/ 1 };
		PathInfo.path_name = PathInfo_path_name;

		TFile* f_tree = NULL;
		TTree* tree = NULL;

		TreeRaw *tree_raw_obj = NULL;

		//loop by runs
		int counter_f_tree = 0;
		for (int run_number = start_run_number; run_number <= stop_run_number; run_number++)
		{
			//create new tree and file
			if ((run_number - start_run_number) % runs_per_tree_file == 0)
			{
				ostringstream f_tree_name;
				f_tree_name << path_name_tree << "ch_" << GetChId(i) << "__block_" << setfill('0') << setw(7) << counter_f_tree << ".root";
				f_tree = TFile::Open(f_tree_name.str().c_str(), "RECREATE");

				tree_raw_obj = new TreeRaw();
				tree = tree_raw_obj->GetTreePnt();
			}

			PathInfo.run_number = run_number;
#pragma omp critical
			{
				//std::cout << "i = " << i << "; ch_id = " << GetChId(i) << "; run_number = " << run_number << ";  thread = " << omp_get_thread_num() << std::endl;
			}

			TStopwatch timer_read_binary;
			timer_read_binary.Start();
			ReadData_CAEN rdt(PathInfo, ch_list, str_comm);
			timer_read_binary.Stop();
			//time_read_binary += timer_read_binary.RealTime();

			//loop by events
			for (int temp_event_id = 0; temp_event_id < PathInfo.events_per_file; temp_event_id++)
			{
				//f_tree->cd();
	#pragma omp critical
				{
					std::cout << "i = " << i << "; ch_id = " << GetChId(i) << "; run_number = " << run_number << ";  thread = " << omp_get_thread_num() << std::endl;
					cout << "tree = " << tree << endl;
					cout << f_tree->GetPath() << endl;
					cout << endl;
					f_tree->cd();
					tree->Fill();
					
				}

			}// end loop by events

			//write tree and close file
			if (((run_number - start_run_number) % runs_per_tree_file == runs_per_tree_file - 1) || (run_number == stop_run_number))
			{
			//	TStopwatch timer_write_and_close;
			//	timer_write_and_close.Start();

				f_tree->cd();
				tree->Write();
				f_tree->Close();

				delete f_tree;
				delete tree_raw_obj;

				tree_raw_obj = NULL;
				f_tree = NULL;
				tree = NULL;

				counter_f_tree++;

			//	timer_write_and_close.Stop();
			//	//time_write_and_close += timer_write_and_close.RealTime();
			}


		}// end loop by runs

	}

	timer_total.Stop();
	std::cout << "-------------------------------" << std::endl;

	std::cout << "total time = " << timer_total.RealTime() << " sec" << std::endl;
	std::cout << "all is ok" << std::endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();
	return 0;
}