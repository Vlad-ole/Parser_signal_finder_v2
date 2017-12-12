#include "TreeInfoAllCh.h"


TreeInfoAllCh::TreeInfoAllCh()
{
	tree = new TTree("TreeInfoAllCh", "TreeInfoAllCh");

	tree->Branch("num_of_pe_in_event_all_ch__positive_part_s_int", &num_of_pe_in_event_all_ch__positive_part_s_int);
	tree->Branch("x_cog", &x_cog);
	tree->Branch("y_cog", &y_cog);
}


TreeInfoAllCh::~TreeInfoAllCh()
{
	delete tree;
}
