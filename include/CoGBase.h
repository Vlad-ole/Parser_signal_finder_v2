#pragma once

#include <iostream>
#include <vector>

class CoGBase
{
public:
	CoGBase(std::vector<double> &num_of_pe_in_event_vec);
	~CoGBase();
	double GetX();
	double GetY();

	double GetXByMax();
	double GetYByMax();

	double GetXCoGModified();
	double GetYCoGModified();

private:
	
	double x;
	double y;

	double x_by_max;
	double y_by_max;

	double x_cog_modified;
	double y_cog_modified;
};

