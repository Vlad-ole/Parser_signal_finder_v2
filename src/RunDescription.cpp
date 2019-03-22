#include "RunDescription.h"

using namespace std;


const int n_ch = 28; //(25 SiPM + 3PMT + 1PMT + GEM)
int GetChId(int array_position)
{	
	//return array_position + 32;
	
	//return 0;
	
	int ch_id;
	
	////if you use 3PMT, 1PMT, GEM and 32 SiPM channels
	//if (array_position >= 0 && array_position <= 2)
	//	ch_id = array_position;
	//else if (array_position >= 3 && array_position < 35)
	//	ch_id = array_position + 32 - 3;
	//else
	//{
	//	cout << "Unknown channel in GetChId " << endl;
	//	system("pause");
	//	exit(1);		
	//}

	////if you use 32 SiPM channels only
	//if (array_position >= 0 && array_position <= 31)
	//	ch_id = array_position + 32;
	//else
	//{
	//	cout << "Unknown channel in GetChId " << endl;
	//	exit(1);
	//}

	//if you use 3PMT, 1PMT, GEM and 25 SiPM channels
	if (array_position >= 0 && array_position <= 2)
		ch_id = array_position;
	else if (array_position >= 3 && array_position <= 15)
		ch_id = array_position + 32 - 3;
	else if (array_position >= 16 && array_position <= 27)
		ch_id = array_position + 32 - 3 + 3;
	else
	{
		cout << "Unknown channel in GetChId " << endl;
		system("pause");
		exit(1);		
	}


	return ch_id;
}

int GetArrayPosition(int ch_id)
{
	int array_position;
	
	//if you use 3PMT, 1PMT, GEM and 25 SiPM channels
	if (ch_id >= 0 && ch_id <= 2)
		array_position = ch_id;
	else if (ch_id >= 32 && ch_id <= 44)
		array_position = ch_id - 29;
	else if (ch_id >= 48 && ch_id <= 59)
		array_position = ch_id - 32;
	else
	{
		cout << "Unknown array_position in GetArrayPosition " << endl;
		system("pause");
		exit(1);
	}
	
	return array_position;
}

int GetChIdSiPM(int array_position)
{
	return array_position + 32;
}

int GetChIdSiPMCorrect(int array_position)
{
	int ch_id;
	if (array_position <= 12)
	{
		ch_id = array_position + 32;
	}
	else if (array_position >= 13 && array_position < 25)
	{
		ch_id = array_position + 32 + 3;
	}

	return ch_id;
}

int GetArrayPositionSiPM(int ch_id)
{
	int array_position;

	//if 25 SiPM channels
	if (ch_id >= 32 && ch_id <= 44)
		array_position = ch_id - 32;
	else if (ch_id >= 48 && ch_id <= 59)
		array_position = ch_id - 3 - 32;
	else
	{
		cout << "Unknown array_position in GetArrayPosition " << endl;
		system("pause");
		exit(1);
	}

	return array_position;
}

const bool is_sipm_ch = true;


////---------------------------------------------
//180830 Ar pure
//
//std::string folder_name = "180830_Xray_0kV_600V_12bB_49V_1ph_35mm_coll\\";
//const int start_run_number = 23;
//const int stop_run_number = 38;
//
//std::string folder_name = "180830_Xray_20kV_600V_12bB_49V_1ph_35mm_coll\\";
//const int start_run_number = 40;
//const int stop_run_number = 49;
//
//
//
//std::string common_path = "E:\\180830\\";
//std::string date = "180830";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
////---------------------------------------------


//////---------------------------------------------
////181220 Ar + 0% CH4
////
//std::string folder_name = "f4_181220_0kV_750V_12dB_49V_coll35_1ph\\";
//const int start_run_number = 13;
//const int stop_run_number = 23;
////
//std::string common_path = "E:\\181220\\";
//std::string date = "181220";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
//////---------------------------------------------

//////---------------------------------------------
////181101 Ar + 10% CH4
////
//std::string folder_name = "f7_181101_0kV_800V_12dB_49V_coll35_1ph\\";
//const int start_run_number = 29;
//const int stop_run_number = 44;
////
//std::string common_path = "E:\\181101\\";
//std::string date = "181101";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
//////---------------------------------------------


////---------------------------------------------
//181213 Ar + 0% CH4
//
//std::string folder_name = "f1_181213_0kV_750V_12dB_49V_coll35_1ph\\";
//const int start_run_number = 1;
//const int stop_run_number = 21;
////
//std::string common_path = "E:\\181213\\";
//std::string date = "181213";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
////---------------------------------------------


////---------------------------------------------
////181025 Ar + 5% CH4
//
//std::string folder_name = "f5_181025_0kV_800V_12bB_49V_coll35_1ph\\";
//const int start_run_number = 18;
//const int stop_run_number = 40;
////
//std::string common_path = "E:\\181025\\";
//std::string date = "181025";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
////---------------------------------------------






////---------------------------------------------
////181018 Ar + 1% CH4
//
//std::string folder_name = "f5_181018_0kV_800V_12bB_49V_coll35_1ph\\";
//const int start_run_number = 17;
//const int stop_run_number = 28;
//
////std::string folder_name = "f10_180913_Xray_0kV_800V_6bB_49V_1ph_35mm_coll\\";
////const int start_run_number = 30;
////const int stop_run_number = 39;
//
//
//
//std::string common_path = "E:\\181018\\";
//std::string date = "181018";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
////---------------------------------------------




////---------------------------------------------
////180913 Ar + 1% CH4
//
////std::string folder_name = "f1_180913_Xray_20kV_800V_6bB_49V_1ph_35mm_coll\\";
////const int start_run_number = 1;
////const int stop_run_number = 3;
//
//std::string folder_name = "f10_180913_Xray_0kV_800V_6bB_49V_1ph_35mm_coll\\";
//const int start_run_number = 30;
//const int stop_run_number = 39;
//
//
//
//std::string common_path = "E:\\180913\\";
//std::string date = "180913";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
////---------------------------------------------






//////---------------------------------------------
////180920 Ar + 0.1% CH4
////
//std::string folder_name = "f11_180920_0kV_800V_12bB_49V_1ph\\";
//const int start_run_number = 91;
//const int stop_run_number = 100;
////
////std::string folder_name = "f6_180920_20kV_800V_12bB_49V_1ph\\";
////const int start_run_number = 66;
////const int stop_run_number = 68;
//
//
//std::string common_path = "E:\\180920\\";
//std::string date = "180920";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
//////---------------------------------------------






//////---------------------------------------------
////181004 Ar + 0.01% CH4
////
//std::string folder_name = "f9_181004_0kV_800V_12bB_49V_1ph\\";
//const int start_run_number = 35;
//const int stop_run_number = 45;
//
//std::string common_path = "E:\\181004\\";
//std::string date = "181004";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
//////---------------------------------------------








////---------------------------------------------
//Feb 22  2018
//
//1000 events per file
//

/*x-ray*/
//
//std::string folder_name = "8kV_SiPM_46V_xray_240Hz\\";
//const int start_run_number = 59;
//const int stop_run_number = 61;
//
//std::string folder_name = "8kV_SiPM_46V_xray_240Hz_PMT_750V\\";
//const int start_run_number = 63;
//const int stop_run_number = 65;
//
//std::string folder_name = "14kV_SiPM_46V_xray_240Hz\\";
//const int start_run_number = 14;
//const int stop_run_number = 16;



//std::string common_path = "E:\\180222\\";
//std::string date = "180222";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;
////---------------------------------------------



////---------------------------------------------
//January 25  2018
//
//1000 events per file
//

/*x-ray*/
//
//std::string folder_name = "x_ray_0kV_PMT650_6dB_without_coll\\";
//const int start_run_number = 1;
//const int stop_run_number = 5;


/*Am*/
//
//std::string folder_name = "Am_20kV_PMT_750_12dB_6mm_coll\\";
//const int start_run_number = 17;
//const int stop_run_number = 63;
//
//std::string folder_name = "Am_20kV_PMT_750_12dB_14mm_coll\\";
//const int start_run_number = 65;
//const int stop_run_number = 106;
//
//std::string folder_name = "Am_20kV_PMT_750_12dB_without_coll\\";
//const int start_run_number = 108;
//const int stop_run_number = 151;


//std::string common_path = "E:\\180125\\";
//std::string date = "180125";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;

////---------------------------------------------





////---------------------------------------------
//December 21 2017
//
//1000 events per file
//

/*Cd*/
//
//std::string folder_name = "Cd_20kV_SiPM_48V_THGEM_0V_coll_6mm_without_int\\";
//const int start_run_number = 153;
//const int stop_run_number = 193;

//std::string folder_name = "Cd_20kV_SiPM_48V_THGEM_0V_coll_2mm_without_int\\";
//const int start_run_number = 195;
//const int stop_run_number = 226;



//std::string common_path = "E:\\171221\\";
//std::string date = "171221";
//std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
//std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;

////---------------------------------------------







////---------------------------------------------
//November 30 2017
//
//1000 events per file
//


/*Cd*/
//
//std::string folder_name = "Bkg_20kV_SiPM_48V_THGEM_2200V_coll_6mm\\";
//const int start_run_number = 571;
//const int stop_run_number = 579;
//
//std::string folder_name = "Cd_20kV_SiPM_48V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 185;
//const int stop_run_number = 221;
//
//std::string folder_name = "Cd_20kV_SiPM_46V_THGEM_2200V_coll_xmm\\";
//const int start_run_number = 376;
//const int stop_run_number = 419;
//
//std::string folder_name = "Cd_14kV_SiPM_46V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 285;
//const int stop_run_number = 306;
//
//std::string folder_name = "Cd_16kV_SiPM_46V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 308;
//const int stop_run_number = 328;
//
std::string folder_name = "Cd_20kV_SiPM_48V_THGEM_2000V_coll_2mm\\";
const int start_run_number = 159;
const int stop_run_number = 183;
//
//std::string folder_name = "Cd_18kV_SiPM_46V_THGEM_2000V_coll_2mm\\";
//const int start_run_number = 1;
//const int stop_run_number = 20;
//
//std::string folder_name = "Cd_18kV_SiPM_48V_THGEM_2000V_coll_2mm\\";
//const int start_run_number = 137;
//const int stop_run_number = 157;
//
//std::string folder_name = "Cd_18kV_SiPM_48V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 223;
//const int stop_run_number = 242;
//
//std::string folder_name = "Cd_18kV_SiPM_46V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 330;
//const int stop_run_number = 352;
//
//std::string folder_name = "Cd_20kV_SiPM_46V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 354;
//const int stop_run_number = 374;
//
//std::string folder_name = "Cd_20kV_SiPM_46V_THGEM_0V_coll_6mm\\";
//const int start_run_number = 581;
//const int stop_run_number = 599;
//
//std::string folder_name = "Cd_18kV_SiPM_46V_THGEM_0V_coll_6mm\\";
//const int start_run_number = 601;
//const int stop_run_number = 616;
//
//std::string folder_name = "Cd_16kV_SiPM_46V_THGEM_0V_coll_6mm\\";
//const int start_run_number = 617;
//const int stop_run_number = 634;
//
//std::string folder_name = "Cd_14kV_SiPM_46V_THGEM_0V_coll_6mm\\";
//const int start_run_number = 636;
//const int stop_run_number = 658;
//
//std::string folder_name = "Cd_20kV_SiPM_46V_THGEM_2000V_coll_2mm\\";
//const int start_run_number = 22;
//const int stop_run_number = 42;
//
//std::string folder_name = "Cd_16kV_SiPM_46V_THGEM_2000V_coll_2mm\\";
//const int start_run_number = 44;
//const int stop_run_number = 63;
//
//std::string folder_name = "Cd_16kV_SiPM_48V_THGEM_2000V_coll_2mm\\";
//const int start_run_number = 108;
//const int stop_run_number = 127;
//
//std::string folder_name = "Cd_16kV_SiPM_48V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 244;
//const int stop_run_number = 261;
//
//std::string folder_name = "Cd_14kV_SiPM_46V_THGEM_2000V_coll_2mm\\";
//const int start_run_number = 65;
//const int stop_run_number = 84;
//
//std::string folder_name = "Cd_14kV_SiPM_48V_THGEM_2000V_coll_2mm\\";
//const int start_run_number = 86;
//const int stop_run_number = 106;
//
//std::string folder_name = "Cd_14kV_SiPM_48V_THGEM_2200V_coll_2mm\\";
//const int start_run_number = 263;
//const int stop_run_number = 283;
//


/*x-ray*/
//
//std::string folder_name = "X_ray_4kV_SiPM_46V_THGEM_0V_coll_6mm\\";
//const int start_run_number = 660;
//const int stop_run_number = 676;



std::string common_path = "E:\\171130\\";
std::string date = "171130";
std::string path_name_tree = common_path + date + "_caen_trees\\" + folder_name;
std::string PathInfo_path_name = common_path + date + "_caen_raw\\" + folder_name;

////---------------------------------------------




////---------------------------------------------
//November 23 2017
//path_info PathInfo = { "", 0, /*1000*/ 10 };

/*x-ray*/
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees_old\\x_ray_20kV_PMT550_0dB_coll_2mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_20kV_PMT550_0dB_coll_2mm\\";
//const int start_run_number = 323;
//const int stop_run_number = 334;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\x_ray_18kV_PMT550_0dB_coll_2mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_18kV_PMT550_0dB_coll_2mm\\";
//const int start_run_number = 311;
//const int stop_run_number = 322;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\x_ray_16kV_PMT550_0dB_coll_2mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_16kV_PMT550_0dB_coll_2mm\\";
//const int start_run_number = 335;
//const int stop_run_number = 347;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\x_ray_14kV_PMT550_0dB_coll_2mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_14kV_PMT550_0dB_coll_2mm\\";
//const int start_run_number = 348;
//const int stop_run_number = 361;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\x_ray_12kV_PMT550_0dB_coll_2mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_12kV_PMT550_0dB_coll_2mm\\";
//const int start_run_number = 362;
//const int stop_run_number = 373;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\x_ray_10kV_PMT550_0dB_coll_2mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_10kV_PMT550_0dB_coll_2mm\\";
//const int start_run_number = 374;
//const int stop_run_number = 384;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\x_ray_6kV_PMT700_0dB_coll_6mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_6kV_PMT700_0dB_coll_6mm\\";
//const int start_run_number = 1;
//const int stop_run_number = 7;
////
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\x_ray_4kV_PMT700_0dB_coll_6mm\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\x_ray_4kV_PMT700_0dB_coll_6mm\\";
//const int start_run_number = 8;
//const int stop_run_number = /*12*/ 12;

/*Cd*/
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_20kV_PMT750_12dB_coll_6mm_real\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_20kV_PMT750_12dB_coll_6mm_real\\";
//const int start_run_number = 140;
//const int stop_run_number = 161;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_20kV_PMT750_12dB_coll_2mm_real\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_20kV_PMT750_12dB_coll_2mm_real\\";
//const int start_run_number = 163;
//const int stop_run_number = 200;
////
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_18kV_PMT750_12dB_coll_6mm_real\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_18kV_PMT750_12dB_coll_6mm_real\\";
//const int start_run_number = 215;
//const int stop_run_number = 243;
////
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_16kV_PMT750_12dB_coll_6mm_real\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_16kV_PMT750_12dB_coll_6mm_real\\";
//const int start_run_number = 245;
//const int stop_run_number = 257;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_14kV_PMT750_12dB_coll_6mm_real\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_14kV_PMT750_12dB_coll_6mm_real\\";
//const int start_run_number = 259;
//const int stop_run_number = 274;


/*Bkg*/
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_20kV_PMT750_12dB_bkg\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_20kV_PMT750_12dB_bkg\\";
//const int start_run_number = 202;
//const int stop_run_number = 213;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_18kV_PMT750_12dB_bkg\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_18kV_PMT750_12dB_bkg\\";
//const int start_run_number = 299;
//const int stop_run_number = 309;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_16kV_PMT750_12dB_bkg\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_16kV_PMT750_12dB_bkg\\";
//const int start_run_number = 287;
//const int stop_run_number = 297;
//
//std::string path_name_tree = "D:\\Data_work\\171123_caen_trees\\Cd_14kV_PMT750_12dB_bkg\\";
//std::string PathInfo_path_name = "D:\\Data_work\\171123_caen_raw\\Cd_14kV_PMT750_12dB_bkg\\";
//const int start_run_number = 276;
//const int stop_run_number = 285;







////---------------------------------------------


////---------------------------------------------
//August 3 2017
//path_info PathInfo = {"", 0, /*1000*/ 1000};

/*Flashlight*/
//
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\sipm_46V\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\sipm_46V\\";
//const int start_run_number = 1;
//const int stop_run_number = /*146*/ 5;
//
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\sipm_46V_run2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\sipm_46V_run2\\";
//const int start_run_number = 399;
//const int stop_run_number = /*522*/ 399;
//
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\sipm_48V\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\sipm_48V\\";
//const int start_run_number = 147;
//const int stop_run_number = 279;
//
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\sipm_48V_run2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\sipm_48V_run2\\";
//const int start_run_number = 399;
//const int stop_run_number = 522;


/*Cd*/
//26000 events, 20 kV, Cd, V(PMT) = 700V, V(SiPM) = 46V, dV(GEM) = 0, internal 2mm, trigger from 3PMT (th = 400 mV) + 6 dB att.; LOW ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\event_20kV_46Vsipm_700Vpmt_int_coll_Cd\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\event_20kV_46Vsipm_700Vpmt_int_coll_Cd\\";
//const int start_run_number = 539;
//const int stop_run_number = 563;
//
////34000 events, 20 kV, Cd, V(PMT) = 700V, V(SiPM) = 48V, dV(GEM) = 2200, internal 2mm, trigger from 3PMT (th = 128 mV) + 6 dB att.
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2200gem_offset\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2200gem_offset\\";
//const int start_run_number = 578;
//const int stop_run_number = 611;
//
//35000 events, 20 kV, Cd, V(PMT) = 700V, V(SiPM) = 48V, dV(GEM) = 2000, internal 2mm, trigger from 3PMT (th = 128 mV) + 6 dB att.
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2000gem_offset\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2000gem_offset\\";
//const int start_run_number = 612;
//const int stop_run_number = /*646*/ 612;
//
//43000 events, 20 kV, Cd, V(PMT) = 700V, V(SiPM) = 46V, dV(GEM) = 2200, no collimator, trigger from 3PMT (th = 128 mV) + 6 dB att.
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\event_20kV_46Vsipm_700Vpmt_without_coll_Cd_2200gem_offset\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\event_20kV_46Vsipm_700Vpmt_without_coll_Cd_2200gem_offset\\";
//const int start_run_number = 1;
//const int stop_run_number = 43;
//
//100000 events, 20 kV, Cd, V(PMT) = 700V, V(SiPM) = 48V, dV(GEM) = 2200, no collimator, trigger from 3PMT (th = 128 mV) + 6 dB att.
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\event_20kV_48Vsipm_700Vpmt_without_coll_Cd_2200gem_offset\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\event_20kV_48Vsipm_700Vpmt_without_coll_Cd_2200gem_offset\\";
//const int start_run_number = 1;
//const int stop_run_number = /*100*/ 1;

////---------------------------------------------
//July 13 2017

//path_info PathInfo = {"", 0, /*1000*/ 1};

/*Cd*/
//63000 events, Cd, V(PMT) = 700V, V(SiPM) = 48V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_20kV_49VSiPM_Cd\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_20kV_49VSiPM_Cd\\";
//const int start_run_number = 191;
//const int stop_run_number = 254;
//
//68000 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_20kV_Cd\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_20kV_Cd\\";
//const int start_run_number = 122;
//const int stop_run_number = /*190*/122;
//
//101000 events, Cd, V(PMT) = 700V, V(SiPM) = 48V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_20kV_49VSiPM_Cd_2mmCol\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_20kV_49VSiPM_Cd_2mmCol\\";
//const int start_run_number = 255;
//const int stop_run_number = 355;
//
//44000 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_18kV_Cd\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2200dVGEM_18kV_Cd\\";
//const int start_run_number = 77;
//const int stop_run_number = 121;

/*X-ray*/
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_20kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_20kV\\";
//const int start_run_number = 55;
//const int stop_run_number = 56;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_20kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_20kV_ped\\";
//const int start_run_number = 57;
//const int stop_run_number = 58;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_18kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_18kV\\";
//const int start_run_number = 49;
//const int stop_run_number = 50;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_18kV_again2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_18kV_again2\\";
//const int start_run_number = 53;
//const int stop_run_number = 54;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_18kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_18kV_ped\\";
//const int start_run_number = 51;
//const int stop_run_number = 52;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_16kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_16kV\\";
//const int start_run_number = 59;
//const int stop_run_number = 60;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_16kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_16kV_ped\\";
//const int start_run_number = 61;
//const int stop_run_number = 62;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_14kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_14kV\\";
//const int start_run_number = 63;
//const int stop_run_number = 64;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_14kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_14kV_ped\\";
//const int start_run_number = 65;
//const int stop_run_number = 66;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_12kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_12kV\\";
//const int start_run_number = 67;
//const int stop_run_number = 68;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_12kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_12kV_ped\\";
//const int start_run_number = 69;
//const int stop_run_number = 70;
//
//3000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_10kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_10kV\\";
//const int start_run_number = 71;
//const int stop_run_number = 73;
//
//3000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\X-ray\\event_2200dVGEM_10kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\X-ray\\event_2200dVGEM_10kV_ped\\";
//const int start_run_number = 74;
//const int stop_run_number = 76;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_20kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_20kV\\";
//const int start_run_number = 27;
//const int stop_run_number = 28;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_20kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_20kV_ped\\";
//const int start_run_number = 29;
//const int stop_run_number = 30;
//
//5000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV\\";
//const int start_run_number = 21;
//const int stop_run_number = 25;
//
//1000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV_ped\\";
//const int start_run_number = 26;
//const int stop_run_number = 26;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV_again2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV_again2\\";
//const int start_run_number = 33;
//const int stop_run_number = 34;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_18kV_ped_again2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_18kV_ped_again2\\";
//const int start_run_number = 31;
//const int stop_run_number = 32;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_16kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_16kV\\";
//const int start_run_number = 35;
//const int stop_run_number = 36;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_16kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_16kV_ped\\";
//const int start_run_number = 37;
//const int stop_run_number = 38;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_14kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_14kV\\";
//const int start_run_number = 39;
//const int stop_run_number = 40;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_14kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_14kV_ped\\";
//const int start_run_number = 41;
//const int stop_run_number = 42;
//
//2000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_10kV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_10kV\\";
//const int start_run_number = 43;
//const int stop_run_number = 44;
//
//3000 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2000dVGEM_10kV_ped\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170713_caen_raw\\Cd\\event_2000dVGEM_10kV_ped\\";
//const int start_run_number = 46;
//const int stop_run_number = 48;

//---------------------------------------------



//---------------------------------------------
//June 22 2017

//path_info PathInfo = { "", 0, /*10*/ 10};

/*Cd*/
//10 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_20_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_20_thmV\\";
//const int start_run_number = 1888;
//const int stop_run_number = 1888;
//
//2230 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_20_th400mV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_20_th400mV\\";
//const int start_run_number = 1889;
//const int stop_run_number = /*2111*/1889;
//
//1620 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_18_th300mV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_18_th300mV\\";
//const int start_run_number = 1722;
//const int stop_run_number = /*1883*/1722;
//
//17180 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_18_th190mV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_18_th190mV\\";
//const int start_run_number = 4;
//const int stop_run_number = 1721;
//
//1860 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_16_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_16_thmV\\";
//const int start_run_number = 2112;
//const int stop_run_number = 2297;
//
//1980 events, Cd, V(PMT) = 700V, V(SiPM) = 46V, HIGH ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_Cd_14_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_Cd_14_thmV\\";
//const int start_run_number = 2298;
//const int stop_run_number = 2495;


/*X-ray*/
//330 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_20_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_20_thmV\\";
//const int start_run_number = 2749;
//const int stop_run_number = 2782;
//
//4180 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x_ray_18_2mmColl\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x_ray_18_2mmColl\\";
//const int start_run_number = 3537;
//const int stop_run_number = 3955 /*3537*/;
//
//2180 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, LOW ELECTRONIC NOISE (but high intensity of light and problems with saturation and PMT signal shifting)
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_18_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_18_thmV\\";
//const int start_run_number = 2496;
//const int stop_run_number = 2714;
//
//270 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_18_small_2\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_18_small_2\\";
//const int start_run_number = 2721;
//const int stop_run_number = 2748;
//
//700 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_16_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_16_thmV\\";
//const int start_run_number = 2783;
//const int stop_run_number = 2853;
//
//600 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_14_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_14_thmV\\";
//const int start_run_number = 2854;
//const int stop_run_number = 2914;
//
//380 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_12_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_12_thmV\\";
//const int start_run_number = 2915;
//const int stop_run_number = 2953;
//
//790 events, X-ray, V(PMT) = 550V, V(SiPM) = 46V
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_10_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_10_thmV\\";
//const int start_run_number = 2954;
//const int stop_run_number = 3033;
//
//330 events, X-ray, V(PMT) = 700V, V(SiPM) = 46V
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_10_thmV_recalib\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_10_thmV_recalib\\";
//const int start_run_number = 3034;
//const int stop_run_number = 3067;
//
//400 events, X-ray, V(PMT) = 700V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_9_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_9_thmV\\";
//const int start_run_number = 3068;
//const int stop_run_number = 3108;
//
//590 events, X-ray, V(PMT) = 700V, V(SiPM) = 46V
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_8_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_8_thmV\\";
//const int start_run_number = 3109;
//const int stop_run_number = 3168;
//
//570 events, X-ray, V(PMT) = 700V, V(SiPM) = 46V
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_7_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_7_thmV\\";
//const int start_run_number = 3169;
//const int stop_run_number = 3226;
//
//640 events, X-ray, V(PMT) = 700V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//std::string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_6_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_6_thmV\\";
//const int start_run_number = 3227;
//const int stop_run_number = 3291;
//
//1030 events, X-ray, V(PMT) = 700V, V(SiPM) = 46V
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_5_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_5_thmV\\";
//const int start_run_number = 3292;
//const int stop_run_number = 3395;
//
//1400 events, X-ray, V(PMT) = 700V, V(SiPM) = 46V, LOW ELECTRONIC NOISE
//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_4_thmV\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_4_thmV\\";
//const int start_run_number = 3396;
//const int stop_run_number = 3536;


//---------------------------------------------