#include "IntermediateTreeInfo.h"


IntermediateTreeInfo::IntermediateTreeInfo() //: tree("tree_intermediate", "Intermediate tree")
{
	tree = new TTree("tree_intermediate", "Intermediate tree");

	tree->Branch("num_of_pe_in_event__positive_part_s_int", &num_of_pe_in_event__positive_part_s_int);	
	tree->Branch("signals_x_start", &signals_x_start);
	//tree->Branch("signals_x_stop", &signals_x_stop);
	//tree->Branch("local_baseline", &local_baseline);
	//tree->Branch("integral_one_peak", &integral_one_peak);
	//tree->Branch("one_peak_y_maximum", &one_peak_y_maximum);	
	//tree->Branch("num_of_pe_in_one_peak", &num_of_pe_in_one_peak);
}


IntermediateTreeInfo::~IntermediateTreeInfo()
{
	delete tree;
}
