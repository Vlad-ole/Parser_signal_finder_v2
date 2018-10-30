#include "PeakFinderFind.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

PeakFinderFind::PeakFinderFind(std::vector<double>& yv, std::vector<double>& yv_der, const double th, const double th_der, const double HORIZ_INTERVAL, bool is_by_amp)
{
	bool is_search = true;
	int position_tmp;
	double max_el;
	double local_baseline;
	pair<int, int> pair_var;

	const double window = 200; //ns
	const double local_baseline_window = 350; //ns
	const double local_baseline_window_shift = 50; //ns
	const double check_overlapping_window = 500; //ns

	const int half_window_p = window / HORIZ_INTERVAL;
	const int local_baseline_window_p = local_baseline_window / HORIZ_INTERVAL;
	const int local_baseline_window_shift_p = local_baseline_window_shift / HORIZ_INTERVAL;
	const int check_overlapping_window_p = check_overlapping_window / HORIZ_INTERVAL;

	//bool is_by_amp = true;

	if (!is_by_amp)
	{
		//th by der
		for (int i = 0; i < yv.size(); i++)
		{
			//cout << yv_der[i] << endl;

			if ((yv_der[i] > th_der) && is_search)
			{
				is_search = false;
				position_tmp = i;

				local_baseline = 0;
				const double j_from = (i - local_baseline_window_shift_p - local_baseline_window_p) > 0 ? i - local_baseline_window_shift_p - local_baseline_window_p : 0;

				for (int j = j_from; j < i - local_baseline_window_shift_p; j++)
				{
					local_baseline += yv[j];
				}

				local_baseline /= (i - local_baseline_window_shift_p - j_from);
				local_baseline_v.push_back(local_baseline);
				//cout << "local_baseline = " << local_baseline << endl;

				for (int j = i; j > j_from; j--)
				{
					if (yv[j] < local_baseline)
					{
						pair_var.first = j;
						break;
					}
				}

			}

			if (!is_search && (i > position_tmp) && (yv_der[i] < th_der))
			{
				if (yv[i] < local_baseline)
				{
					bool is_overlapped = false;
					if ((i + check_overlapping_window_p) < yv.size())
					{
						for (int j = i; j < i + check_overlapping_window_p; j++)
						{
							if (abs(yv_der[j]) > th_der)
							{
								is_overlapped = true;
								break;
							}
						}

					}


					if (!is_overlapped)
					{
						is_search = true;
						pair_var.second = i;
						pair_v.push_back(pair_var);
						//cout << pair_var.first << "\t" << pair_var.second << endl;
					}
				}
			}

			//if (!is_search)
			//{
			//	if (yv[i] > pair_value.second)
			//	{
			//		pair_value.first = i;
			//		pair_value.second = yv[i];
			//	}
			//}

			//if ((yv[i] < th) && !is_search)
			//{
			//	is_search = true;
			//	peak_position.push_back(pair_value.first);
			//}
		}
	}



	if (is_by_amp)
	{


		//th by amp
		for (int i = 0; i < yv.size(); i++)
		{
			//cout << yv_der[i] << endl;

			if ((yv[i] > th) && is_search)
			{
				is_search = false;
				position_tmp = i;

				local_baseline = 0;
				const double j_from = (i - local_baseline_window_shift_p - local_baseline_window_p) > 0 ? i - local_baseline_window_shift_p - local_baseline_window_p : 0;

				for (int j = j_from; j < i - local_baseline_window_shift_p; j++)
				{
					local_baseline += yv[j];
				}

				local_baseline /= (i - local_baseline_window_shift_p - j_from);
				local_baseline_v.push_back(local_baseline);
				//cout << "local_baseline = " << local_baseline << endl;

				for (int j = i; j > j_from; j--)
				{
					if (yv[j] < local_baseline)
					{
						pair_var.first = j;
						break;
					}
				}

			}

			if (!is_search && (i > position_tmp) && (yv[i] < th))
			{
				if (yv[i] < local_baseline)
				{
					bool is_overlapped = false;
					if ((i + check_overlapping_window_p) < yv.size())//can be error
					{
						for (int j = i; j < i + check_overlapping_window_p; j++)
						{
							if (yv[j] > th)//error?
							{
								is_overlapped = true;
								break;
							}
						}
					}

					if (!is_overlapped)
					{
						is_search = true;
						pair_var.second = i;
						pair_v.push_back(pair_var);
						//cout << pair_var.first << "\t" << pair_var.second << endl;
					}
				}
			}

			//if (!is_search)
			//{
			//	if (yv[i] > pair_value.second)
			//	{
			//		pair_value.first = i;
			//		pair_value.second = yv[i];
			//	}
			//}

			//if ((yv[i] < th) && !is_search)
			//{
			//	is_search = true;
			//	peak_position.push_back(pair_value.first);
			//}
		}
	}

}


PeakFinderFind::~PeakFinderFind()
{
}
