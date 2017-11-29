#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

struct path_info
{
	std::string path_name;
	int run_number;
	int events_per_file;
	//path_info();
};


struct ch_info
{
	int id;
	double VERTICAL_OFFSET;
	double VERTICAL_GAIN;
};

struct comm_info
{
	int write_type;
	double HORIZ_INTERVAL;
	double time_offset;
	int WAVE_ARRAY_COUNT;
};


class ReadData
{
public:
	ReadData();
	virtual ~ReadData() = 0;
	virtual std::vector< std::vector< std::vector<double> > >& GetDataDouble();
	virtual std::vector<double>& GetTimeArray();
protected:
	std::vector< std::vector<short int> > data;//old variant
	std::vector< std::vector< std::vector<double> > > data_double;//several events in one run; several ch in one run; many data points
	std::vector<double> time;
};

