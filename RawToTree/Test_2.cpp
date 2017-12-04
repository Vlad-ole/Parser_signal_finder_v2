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


	TThread::Initialize();

#pragma omp parallel for num_threads(4)
	for (int i = 0; i < n_ch; i++)
	{
		
		TreeRaw *tree_raw_obj = NULL;
		TFile *f_tree = NULL;
		TTree *tree = NULL;

#pragma omp critical
		{			
			tree_raw_obj = new TreeRaw();
			tree = tree_raw_obj->GetTreePnt();

			int counter_f_tree = 0;
			
			ostringstream f_tree_name;
			f_tree_name << path_name_tree << "ch_" << GetChId(i) << "__block_" << setfill('0') << setw(7) << counter_f_tree << ".root";
			f_tree = TFile::Open(f_tree_name.str().c_str(), "RECREATE");

			std::cout << "i = " << i << "; ch_id = " << GetChId(i) << "; run_number = " << ";  thread = " << omp_get_thread_num() << std::endl;
		}

			vector<double> tmp_vec_1(10, 1);
			vector<double> tmp_vec_2(10, 2);
			vector<double> tmp_vec_3(10, 3);

			tree_raw_obj->data_raw = tmp_vec_1;
			tree_raw_obj->data_der = tmp_vec_2;
			tree_raw_obj->data_without_slope = tmp_vec_3;
			tree_raw_obj->baseline = 12;
			tree_raw_obj->ch_id = GetChId(i);
			tree_raw_obj->event_id = GetChId(i) + 1000;
			tree_raw_obj->min_element = -1;
			tree_raw_obj->max_element = 1;

			//f_tree->cd();
			//tree->SetDirectory();
			//cout << "tree->GetDirectory()->GetPath() = " << tree->GetDirectory()->GetPath() << endl;
			//cout << "f_tree->GetPath() = " << f_tree->GetPath() << endl;
		
			
			f_tree->cd();
			//cout << "f_tree->GetPath() = " << f_tree->GetPath() << endl;

			tree->Fill();
			
	
			tree->Write();	
			f_tree->Close();


			delete tree_raw_obj;

			tree_raw_obj = NULL;
			tree = NULL;		
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