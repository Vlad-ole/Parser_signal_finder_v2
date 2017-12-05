#include "TreeInfo.h"


TreeInfo::TreeInfo()
{
	tree = new TTree("tree_info", "Tree info");

	tree->Branch("HORIZ_INTERVAL", &HORIZ_INTERVAL);
	tree->Branch("WAVE_ARRAY_COUNT", &WAVE_ARRAY_COUNT);
	tree->Branch("runs_per_tree_file", &runs_per_tree_file);
	tree->Branch("n_ch", &n_ch);
	tree->Branch("n_blocks", &n_blocks);
}


TreeInfo::~TreeInfo()
{
	delete tree;
}
