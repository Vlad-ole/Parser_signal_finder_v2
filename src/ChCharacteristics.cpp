#include "ChCharacteristics.h"

using namespace std;

double ChCharacteristics::step_x = 10; //mm
double ChCharacteristics::step_y = 10; //mm

std::vector<ChCharacteristicsStruct> ChCharacteristics::ch_characteristics_struct =
//amp#1, V(SiPM) = 46V
//{
//		{ 32, true, true, 1482, 750, 3000, -2 * step_x, 2 * step_y },
//		{ 33, true, true, 1256, 750, 3000, -step_x, 2 * step_y },
//		{ 34, true, true, 1622, 750, 3000, 2 * step_x, 2 * step_y },
//		{ 35, true, true, 1569, 750, 3000, -2 * step_x, step_y },
//		{ 36, true, true, 1654, 750, 3000, step_x, step_y },
//		{ 37, true, true, 1419, 750, 3000, 2 * step_x, step_y },
//		{ 38, true, true, 1705, 750, 3000, 0, 0 },
//		{ 39, true, true, 1565, 750, 3000, step_x, 0 },
//		{ 40, true, true, 1548, 750, 3000, -step_x, -step_y },
//		{ 41, true, true, 1594, 750, 3000, 0, -step_y },
//		{ 42, true, true, 1564, 750, 3000, -2 * step_x, -2 * step_y },
//		{ 43, true, true, 1581, 750, 3000, -step_x, -2 * step_y },
//		{ 44, true, false, 828, 0, 3000, 2 * step_x, -2 * step_y },
//		{ 48, true, true, 1540, 750, 3000, 0, 2 * step_y },
//		{ 49, true, true, 1210, 500, 3000, step_x, 2 * step_y },
//		{ 50, true, true, 1307, 750, 3000, -step_x, step_y },
//		{ 51, true, true, 1528, 750, 3000, 0, step_y },
//		{ 52, true, true, 1771, 750, 3000, -2 * step_x, 0 },
//		{ 53, true, true, 1769, 750, 3000, -step_x, 0 },
//		{ 54, true, true, 1493, 750, 3000, 2 * step_x, 0 },
//		{ 55, true, true, 1561.59, 750, 3000, -2 * step_x, -step_y },
//		{ 56, true, false, 0, 750, 3000, step_x, -step_y },
//		{ 57, true, true, 1592.03, 750, 3000, 2 * step_x, -step_y },
//		{ 58, true, true, 1535, 750, 3000, 0, -2 * step_y },
//		{ 59, true, true, 1543, 750, 3000, step_x, -2 * step_y }
//};
//
//amp#1, V(SiPM) = 48V
//{
//	{ 32, true, true, 2239, 750, 3000, -2 * step_x, 2 * step_y },
//	{ 33, true, true, 2048, 750, 3000, -step_x, 2 * step_y },
//	{ 34, true, true, 2611, 750, 3000, 2 * step_x, 2 * step_y },
//	{ 35, true, true, 2650, 750, 3000, -2 * step_x, step_y },
//	{ 36, true, true, 2554, 750, 3000, step_x, step_y },
//	{ 37, true, true, 2220, 750, 3000, 2 * step_x, step_y },
//	{ 38, true, true, 2779, 750, 3000, 0, 0 },
//	{ 39, true, true, 2576, 750, 3000, step_x, 0 },
//	{ 40, true, true, 2584, 750, 3000, -step_x, -step_y },
//	{ 41, true, true, 2515, 750, 3000, 0, -step_y },
//	{ 42, true, true, 2485, 750, 3000, -2 * step_x, -2 * step_y },
//	{ 43, true, true, 2522, 750, 3000, -step_x, -2 * step_y },
//	{ 44, true, false, 1272, 0, 3000, 2 * step_x, -2 * step_y },
//	{ 48, true, true, 2392, 750, 3000, 0, 2 * step_y },
//	{ 49, true, true, 2047, 500, 3000, step_x, 2 * step_y },
//	{ 50, true, true, 2187, 750, 3000, -step_x, step_y },
//	{ 51, true, true, 2450, 750, 3000, 0, step_y },
//	{ 52, true, true, 2676, 750, 3000, -2 * step_x, 0 },
//	{ 53, true, true, 2829, 750, 3000, -step_x, 0 },
//	{ 54, true, true, 2404, 750, 3000, 2 * step_x, 0 },
//	{ 55, true, true, 2466, 750, 3000, -2 * step_x, -step_y },
//	{ 56, true, false, 0, 750, 3000, step_x, -step_y },
//	{ 57, true, true, 2718, 750, 3000, 2 * step_x, -step_y },
//	{ 58, true, true, 2482, 750, 3000, 0, -2 * step_y },
//	{ 59, true, true, 2451, 750, 3000, step_x, -2 * step_y }
//};
//
//amp#5, V(SiPM) = 48V (spe by left edge)
//{
//	{ 32, true, true, 2184, 1800, 3000, -2 * step_x, 2 * step_y },
//	{ 33, true, true, 2015, 1800, 3000, -step_x, 2 * step_y },
//	{ 34, true, true, 2265, 1800, 3000, 2 * step_x, 2 * step_y },
//	{ 35, true, true, 2292, 1800, 3000, -2 * step_x, step_y },
//	{ 36, true, true, 2373, 1800, 3000, step_x, step_y },
//	{ 37, true, true, 2124, 1800, 3000, 2 * step_x, step_y },
//	{ 38, true, true, 2402, 1800, 3000, 0, 0 },
//	{ 39, true, true, 2295, 1800, 3000, step_x, 0 },
//	{ 40, true, true, 2235, 1800, 3000, -step_x, -step_y },
//	{ 41, true, true, 2225, 1800, 3000, 0, -step_y },
//	{ 42, true, true, 2201, 1800, 3000, -2 * step_x, -2 * step_y },
//	{ 43, true, true, 2285, 1800, 3000, -step_x, -2 * step_y },
//	{ 44, true, false, 0, 1800, 3000, 2 * step_x, -2 * step_y },
//	{ 48, true, true, 2228, 1800, 3000, 0, 2 * step_y },
//	{ 49, true, true, 1956, 1800, 3000, step_x, 2 * step_y },
//	{ 50, true, true, 2004, 1800, 3000, -step_x, step_y },
//	{ 51, true, true, 2169, 1800, 3000, 0, step_y },
//	{ 52, true, true, 2358, 1800, 3000, -2 * step_x, 0 },
//	{ 53, true, true, 2457, 1800, 3000, -step_x, 0 },
//	{ 54, true, true, 2155, 1800, 3000, 2 * step_x, 0 },
//	{ 55, true, true, 2180, 1800, 3000, -2 * step_x, -step_y },
//	{ 56, true, true, 2256, 1800, 3000, step_x, -step_y },
//	{ 57, true, true, 2275, 1800, 3000, 2 * step_x, -step_y },
//	{ 58, true, true, 2238, 1800, 3000, 0, -2 * step_y },
//	{ 59, true, true, 2267, 1800, 3000, step_x, -2 * step_y }
//};
//
//amp#5, V(SiPM) = 48V (spe by mean, including afterpulses)
{
	{ 32, true, true, 2647, 1800, 3000, -2 * step_x, 2 * step_y },
	{ 33, true, true, 2281, 1800, 3000, -step_x, 2 * step_y },
	{ 34, true, true, 2834, 1800, 3000, 2 * step_x, 2 * step_y },
	{ 35, true, true, 2837, 1800, 3000, -2 * step_x, step_y },
	{ 36, true, true, 2887, 1800, 3000, step_x, step_y },
	{ 37, true, true, 2519, 1800, 3000, 2 * step_x, step_y },
	{ 38, true, true, 3005, 1800, 3000, 0, 0 },
	{ 39, true, true, 2779, 1800, 3000, step_x, 0 },
	{ 40, true, true, 2718, 1800, 3000, -step_x, -step_y },
	{ 41, true, true, 2806, 1800, 3000, 0, -step_y },
	{ 42, true, true, 2784, 1800, 3000, -2 * step_x, -2 * step_y },
	{ 43, true, true, 2813, 1800, 3000, -step_x, -2 * step_y },
	{ 44, true, false, 0, 1800, 3000, 2 * step_x, -2 * step_y },
	{ 48, true, true, 2736, 1800, 3000, 0, 2 * step_y },
	{ 49, true, true, 2229, 1800, 3000, step_x, 2 * step_y },
	{ 50, true, true, 2303, 1800, 3000, -step_x, step_y },
	{ 51, true, true, 2694, 1800, 3000, 0, step_y },
	{ 52, true, true, 2890, 1800, 3000, -2 * step_x, 0 },
	{ 53, true, true, 3064, 1800, 3000, -step_x, 0 },
	{ 54, true, true, 2621, 1800, 3000, 2 * step_x, 0 },
	{ 55, true, true, 2654, 1800, 3000, -2 * step_x, -step_y },
	{ 56, true, true, 2756, 1800, 3000, step_x, -step_y },
	{ 57, true, true, 2781, 1800, 3000, 2 * step_x, -step_y },
	{ 58, true, true, 2735, 1800, 3000, 0, -2 * step_y },
	{ 59, true, true, 2804, 1800, 3000, step_x, -2 * step_y }
};




//ChCharacteristics::~ChCharacteristics()
//{
//}

vector<ChCharacteristicsStruct>& ChCharacteristics::GetChCharacteristics()
{
	return ch_characteristics_struct;
}
