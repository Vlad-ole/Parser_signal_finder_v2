#pragma once

#include <iostream>
#include "ReadData.h"

int GetChId(int array_position);
int GetChIdSiPM(int array_position);
extern const bool is_sipm_ch;

extern std::string path_name_tree;
extern std::string PathInfo_path_name;
extern const int start_run_number;
extern const int stop_run_number;
extern path_info PathInfo;
