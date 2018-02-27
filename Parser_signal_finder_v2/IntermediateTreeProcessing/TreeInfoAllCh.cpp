#include "TreeInfoAllCh.h"


TreeInfoAllCh::TreeInfoAllCh()
{
	tree = new TTree("TreeInfoAllCh", "TreeInfoAllCh");

	tree->Branch("num_of_pe_in_event_all_ch__positive_part_s_int", &num_of_pe_in_event_all_ch__positive_part_s_int);
	
	tree->Branch("x_cog", &x_cog);
	tree->Branch("y_cog", &y_cog);

	tree->Branch("x_by_max", &x_by_max);
	tree->Branch("y_by_max", &y_by_max);

	tree->Branch("x_cog_modified", &x_cog_modified);
	tree->Branch("y_cog_modified", &y_cog_modified);
}


TreeInfoAllCh::~TreeInfoAllCh()
{
	delete tree;
}
