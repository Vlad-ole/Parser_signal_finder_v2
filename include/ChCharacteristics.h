#pragma once

#include <iostream>
#include <vector>

struct ChCharacteristicsStruct
{
	int ch_id;

	//SinglePeCharacteristics
	bool is_physical;
	bool is_spe_separated_from_noise;
	double spe_mean;
	double spe_min;
	double spe_max;

	//ChPosition
	double x_position;
	double y_position;

};

class ChCharacteristics
{
public:
	//ChCharacteristics();
	//~ChCharacteristics();
	static std::vector<ChCharacteristicsStruct>& GetChCharacteristics();
private:
	static double step_x;
	static double step_y;
	static std::vector<ChCharacteristicsStruct> ch_characteristics_struct;
};



//extern std::vector<SinglePeCharacteristics> single_pe_characteristics;
//extern std::vector<ChPosition> ch_position;