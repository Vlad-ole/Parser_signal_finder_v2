#include "CoGBase.h"
#include "ChCharacteristics.h"
#include "RunDescription.h"
//#include <tuple>

using namespace std;

CoGBase::CoGBase(std::vector<double> &num_of_pe_in_event_vec)
{
	//var1: central row, central column
	x = 0;
	y = 0;
	double n_pe_x = 0;
	double n_pe_y = 0;

	//it is not ideal code, but right now I do not know how to make it better
	
	
	for (int i = 0; i < num_of_pe_in_event_vec.size(); i++)
	{
		int ch = GetChIdSiPMCorrect(i);

		////central row & col
		//bool is_central_row = ch == 52 || ch == 53 || ch == 38 || ch == 39 || ch == 54;
		//bool is_cental_col = ch == 48 || ch == 51 || ch == 38 || ch == 41 || ch == 58;

		////3x5 & 5x3
		//bool is_ch_for_x_5x3 =
		//	ch == 32 || ch == 33 || ch == 48 || ch == 49 || ch == 34 ||
		//	ch == 35 || ch == 50 || ch == 51 || ch == 36 || ch == 37 ||
		//	ch == 52 || ch == 53 || ch == 38 || ch == 39 || ch == 54;

		//bool is_ch_for_y_3x5 =
		//	ch == 32 || ch == 33 || ch == 48 ||
		//	ch == 35 || ch == 50 ||	ch == 51 || 
		//	ch == 52 || ch == 53 || ch == 38 || 
		//	ch == 55 || ch == 40 || ch == 41 || 
		//	ch == 42 || ch == 43 || ch == 58;

		////4x5 & 5x4
		//bool is_ch_for_x_5x4 =
		//	ch == 32 || ch == 33 || ch == 48 || ch == 49 || ch == 34 ||
		//	ch == 35 || ch == 50 || ch == 51 || ch == 36 || ch == 37 ||
		//	ch == 52 || ch == 53 || ch == 38 || ch == 39 || ch == 54 ||
		//	ch == 55 || ch == 40 || ch == 41 || ch == 56 || ch == 57;

		//bool is_ch_for_y_4x5 =
		//	ch == 32 || ch == 33 || ch == 48 || ch == 49 || 
		//	ch == 35 || ch == 50 || ch == 51 || ch == 36 || 
		//	ch == 52 || ch == 53 || ch == 38 || ch == 39 ||
		//	ch == 55 || ch == 40 || ch == 41 || ch == 56 ||
		//	ch == 42 || ch == 43 || ch == 58 || ch == 59;

		////var 1
		//bool ch_for_x = is_central_row;
		//bool ch_for_y = is_cental_col;

		//var 2
		//bool ch_for_x = is_ch_for_x_5x3;
		//bool ch_for_y = is_ch_for_y_3x5;

		//var3
		/*bool ch_for_x = is_ch_for_x_5x4;
		bool ch_for_y = is_ch_for_y_4x5;*/	

		//var4 for the whole matrix
		bool ch_for_x = true;
		bool ch_for_y = true;


		//for y
		if (ch_for_y)
		{
			for (int j = 0; j < ChCharacteristics::GetChCharacteristics().size(); j++)
			{
				if (ChCharacteristics::GetChCharacteristics()[j].ch_id == ch)
				{					
					y += num_of_pe_in_event_vec[i] * ChCharacteristics::GetChCharacteristics()[j].y_position;
					n_pe_y += num_of_pe_in_event_vec[i];
					break;
				}
			}			
		}

		//for x
		if (ch_for_x)
		{
			for (int j = 0; j < ChCharacteristics::GetChCharacteristics().size(); j++)
			{
				if (ChCharacteristics::GetChCharacteristics()[j].ch_id == ch)
				{
					x += num_of_pe_in_event_vec[i] * ChCharacteristics::GetChCharacteristics()[j].x_position;
					n_pe_x += num_of_pe_in_event_vec[i];
					break;
				}
			}
		}

	}



	if (n_pe_y == 0 || n_pe_x == 0)
	{
		cout << "n_pe_y == 0 || n_pe_x == 0" << endl;
		//system("pause");
		//exit(1);
	}
	else
	{
		y /= n_pe_y;
		x /= n_pe_x;
	}
	
	
}

CoGBase::~CoGBase()
{
}

double CoGBase::GetX()
{
	return x;
}

double CoGBase::GetY()
{
	return y;
}
