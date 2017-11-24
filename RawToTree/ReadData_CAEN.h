#pragma once
#include "ReadData.h"
class ReadData_CAEN :
	public ReadData
{
public:
	ReadData_CAEN(path_info PathInfo, const std::vector<ch_info> ch_list, struct comm_info str_comm);
	~ReadData_CAEN();
};

