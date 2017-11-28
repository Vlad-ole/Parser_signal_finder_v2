#include "TreeInfo.h"

using namespace std;

TreeInfo::TreeInfo()
{
	tree = new TTree("t1", "Parser tree");
	
	tree->Branch("run_id", &run_number);
	tree->Branch("event_id", &event_id);
	tree->Branch("ch_id", &ch_id);

	tree->Branch("min_element", &min_element);
	tree->Branch("max_element", &max_element);
	tree->Branch("baseline", &baseline);

	tree->Branch("data_raw", &data_raw);
	tree->Branch("data_der", &data_der);
}


TreeInfo::~TreeInfo()
{
	delete tree;
}

TTree* TreeInfo::GetTreePnt()
{
	return tree;
}
