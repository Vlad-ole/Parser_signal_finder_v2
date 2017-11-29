#include "ReadData_CAEN.h"
#include <sstream>
#include <iomanip>

using namespace std;




ReadData_CAEN::ReadData_CAEN(path_info PathInfo, const std::vector<ch_info> ch_list, struct comm_info str_comm)
{
	//ofstream f_out("D://Data_work//test_folder//test.txt");
	//vectors initialisation
	//-------------------------------------
	//data.resize(PathInfo.events_per_file);
	data_double.resize(PathInfo.events_per_file);
	for (int temp_event_id = 0; temp_event_id < PathInfo.events_per_file; temp_event_id++)
	{
		//data[temp_event_id].resize(ch_list.size());
		data_double[temp_event_id].resize(ch_list.size());
		for (int ch = 0; ch < ch_list.size(); ch++)
		{
			//data[temp_event_id][ch].resize(str_comm.WAVE_ARRAY_COUNT);
			data_double[temp_event_id][ch].resize(str_comm.WAVE_ARRAY_COUNT);
		}
	}
		
	time.resize(str_comm.WAVE_ARRAY_COUNT);
	for (int i = 0; i < str_comm.WAVE_ARRAY_COUNT; i++)
	{
		time[i] = i * str_comm.HORIZ_INTERVAL;
	}
	//-------------------------------------

	const int run_size = PathInfo.events_per_file * str_comm.WAVE_ARRAY_COUNT;

	for (int ch = 0; ch < ch_list.size(); ch++)
	{
		//data[i].resize(vsize);
		//data_double[i].resize(vsize);

		vector<short int> data_tmp;
		data_tmp.resize(run_size);

		stringstream file_full_path;
		file_full_path << PathInfo.path_name << "run_" << PathInfo.run_number <<  "__ch_" << ch_list[ch].id << ".dat";

		//cout << "file_full_path = " << file_full_path.str() << endl;
		//file.open(file_full_path.str());
		//I do not why, but c++ style of reading gives unexpected result, i.e. incorrect reading
		//so I chose usual c-style.
		//The problem in structures. I should use #pragma pack to write structures correctry to the disc.

		FILE *f = fopen(file_full_path.str().c_str(), "rb");

		if (/*!file.is_open()*/f == NULL)
		{
			cout << "can't open this file: " << file_full_path.str() << endl;
			system("pause");
			fclose(f);
			exit(1);
		}

		fread(&data_tmp[0], sizeof(vector<short int>::value_type), run_size, f);
		fclose(f);

		//y points to volts
		for (int temp_event_id = 0; temp_event_id < PathInfo.events_per_file; temp_event_id++)
		{
			for (int j = 0; j < str_comm.WAVE_ARRAY_COUNT; j++)
			{
				const int abs_point = j + temp_event_id*str_comm.WAVE_ARRAY_COUNT;
				//data_double[i][j] = (ch_list[i].VERTICAL_GAIN * data[i][j] - ch_list[i].VERTICAL_OFFSET) * 1000/*V -> mV */;
				data_double[temp_event_id][ch][j] = ((2 / 4095.0) * data_tmp[abs_point] - 1) * 1000;
				//cout << i << " " << j << " " << data[i][j] << " " <<  data_double[i][j] << endl;
				//if (ch == 0)
				//{
				//	f_out << j << "\t" << temp_event_id << "\t" << data_tmp[abs_point] << "\t" << data_double[temp_event_id][ch][j] << endl;
				//}
			}
		}		

	}

}


ReadData_CAEN::~ReadData_CAEN()
{
}
