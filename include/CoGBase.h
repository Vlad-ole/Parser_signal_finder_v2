#pragma once

#include <iostream>
#include <vector>

class CoGBase
{
public:
	CoGBase(std::vector<double> &num_of_pe_in_event_vec, bool is_cog = true);
	~CoGBase();
	double GetX();
	double GetY();
private:
	double x;
	double y;
};

