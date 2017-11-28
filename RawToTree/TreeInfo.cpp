#include "TreeInfo.h"


TreeInfo::TreeInfo()
{
	tree = new TTree("t1", "Parser tree");
	
	tree->Branch("run_id", &run_number);
	tree->Branch("event_id", &event_id);
	tree->Branch("ch_id", &ch_id);

}


TreeInfo::~TreeInfo()
{
	delete tree;
}

TTree* TreeInfo::GetTreePnt()
{
	return tree;
}
