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

using namespace std;

int main(int argc, char *argv[])
{
	TStopwatch timer_total;	
	timer_total.Start();

	double time_read_binary = 0;
	
	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);	
	
	const int n_ch = /*35*/ /*32*/ 32;

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
	int counter_f_tree = 0;

		
	
	//loop by ch
	for (int i = 0; i < n_ch; i++)
	{
		vector<ch_info> ch_list;
		ch_list.resize(1);
		ch_list[0].id = GetChId(i);

		//loop by run
		for (int run_number = start_run_number; run_number <= stop_run_number; run_number++)
		{
			PathInfo.run_number = run_number;
			cout << "ch_id = " << GetChId(i) << "; run_number = " << run_number << endl;
			
			TStopwatch timer_read_binary;
			timer_read_binary.Start();
			ReadData_CAEN rdt(PathInfo, ch_list, str_comm);
			timer_read_binary.Stop();
			time_read_binary += timer_read_binary.RealTime();
		}// end loop by run


	}//end loop by ch


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