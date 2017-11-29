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

using namespace std;

int main(int argc, char *argv[])
{
	TStopwatch timer_total;
	timer_total.Start();

	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);
	


	//vector<int> tmp_vec_int_1(10, 1);

	//IntermediateTreeInfo *obj_heap = new IntermediateTreeInfo();
	////IntermediateTreeInfo obj_stack;

	//

	//ostringstream f_tree_intermediate_name;
	//f_tree_intermediate_name << path_name_tree << "tree_intermediate.root";
	//cout << f_tree_intermediate_name.str().c_str() << endl;
	//TFile* f_tree_intermediate = TFile::Open(f_tree_intermediate_name.str().c_str(), "RECREATE");

	///*obj_stack.num_of_pe_in_event__positive_part_s_int = 100;		
	//obj_stack.signals_x_start = tmp_vec_int_1;
	//obj_stack.tree->Fill();
	//obj_stack.tree->Write();*/

	//obj_heap->num_of_pe_in_event__positive_part_s_int = 100;
	//obj_heap->signals_x_start = tmp_vec_int_1;
	//obj_heap->tree->Fill();
	//obj_heap->tree->Write();

	//f_tree_intermediate->Close();








	vector<int> tmp_vec_int_1(10, 1);

	TFile* f_tree = NULL;
	TTree* tree = NULL;
	IntermediateTreeInfo *tree_raw_obj = NULL;

	ostringstream f_tree_name;
	f_tree_name << path_name_tree << "tree_intermediate.root";
	f_tree = TFile::Open(f_tree_name.str().c_str(), "RECREATE");

	tree_raw_obj = new IntermediateTreeInfo();
	tree = tree_raw_obj->tree;
	tree_raw_obj->num_of_pe_in_event__positive_part_s_int = 14;
	tree_raw_obj->signals_x_start = tmp_vec_int_1;

	tree->Fill();

	tree->Write();
	f_tree->Close();

	delete f_tree;
	delete tree_raw_obj;

	tree_raw_obj = NULL;
	f_tree = NULL;
	tree = NULL;



	timer_total.Stop();
	cout << "total time = " << timer_total.RealTime() << " sec" << endl;
	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();

	return 0;
}