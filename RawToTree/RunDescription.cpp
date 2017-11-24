#include "RunDescription.h"

using namespace std;

int GetChId(int array_position)
{	
	//return array_position + 32;
	
	//return 0;
	
	int ch_id;
	
	//if you use 3PMT, 1PMT, GEM and 32 SiPM channels
	if (array_position >= 0 && array_position <= 2)
		ch_id = array_position;
	else if (array_position >= 3 && array_position < 35)
		ch_id = array_position + 32 - 3;
	else
	{
		cout << "Unknown channel in GetChId " << endl;
		system("pause");
		exit(1);		
	}

	////if you use 32 SiPM channels only
	//if (array_position >= 0 && array_position <= 31)
	//	ch_id = array_position + 32;
	//else
	//{
	//	cout << "Unknown channel in GetChId " << endl;
	//	exit(1);
	//}


	return ch_id;
}

int GetChIdSiPM(int array_position)
{
	return array_position + 32;
}

const bool is_sipm_ch = true;

////---------------------------------------------
//August 3 2017
path_info PathInfo = {"", 0, /*1000*/ 50};

/*Flashlight*/
//
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\sipm_46V\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\sipm_46V\\";
//const int start_run_number = 1;
//const int stop_run_number = /*146*/ 1;
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
//const int stop_run_number = 564;
//
////34000 events, 20 kV, Cd, V(PMT) = 700V, V(SiPM) = 48V, dV(GEM) = 2200, internal 2mm, trigger from 3PMT (th = 128 mV) + 6 dB att.
//std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2200gem_offset\\";
//std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2200gem_offset\\";
//const int start_run_number = 578;
//const int stop_run_number = 611;
//
//35000 events, 20 kV, Cd, V(PMT) = 700V, V(SiPM) = 48V, dV(GEM) = 2000, internal 2mm, trigger from 3PMT (th = 128 mV) + 6 dB att.
std::string path_name_tree = "D:\\Data_work\\170803_caen_trees\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2000gem_offset\\";
std::string PathInfo_path_name = "D:\\Data_work\\170803_caen_raw\\event_20kV_48Vsipm_700Vpmt_int_coll_Cd_2000gem_offset\\";
const int start_run_number = 612;
const int stop_run_number = 646;
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
//const int stop_run_number = 100;

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