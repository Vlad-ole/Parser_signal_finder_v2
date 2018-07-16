#include "TreeRaw.h"

using namespace std;

TreeRaw::TreeRaw() //: tree("tree_raw", "Tree raw")
{
	tree = new TTree("tree_raw", "Tree raw");
	
	tree->Branch("run_id", &run_number);
	tree->Branch("event_id", &event_id);
	tree->Branch("ch_id", &ch_id);

	tree->Branch("min_element", &min_element);
	tree->Branch("max_element", &max_element);
	tree->Branch("baseline", &baseline);

	tree->Branch("data_raw", &data_raw);
	//tree->Branch("data_der", &data_der);
	//tree->Branch("data_without_slope", &data_without_slope);
}


TreeRaw::~TreeRaw()
{
	delete tree;
}

TTree *TreeRaw::GetTreePnt()
{
	return tree;
}
