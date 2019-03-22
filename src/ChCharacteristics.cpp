#include "ChCharacteristics.h"

using namespace std;

double ChCharacteristics::step_x = 10; //mm
double ChCharacteristics::step_y = 10; //mm

const double th = 1000;

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
//amp#5, V(SiPM) = 48V (spe by mean, including afterpulses); th=1800(low noise), th=1000(high noise) (all ch coordinates are correct)
{
	{ 32, true, true, 2647, th, 3000, -2 * step_x, 2 * step_y }, /*ok*/
	{ 33, true, true, 2281, th, 3000, -step_x, 2 * step_y }, /*ok*/
	{ 34, true, true, 2834, th, 3000, 2 * step_x, 2 * step_y }, /*ok*/
	{ 35, true, true, 2837, th, 3000, -2 * step_x, step_y }, /*ok*/
	{ 36, true, true, 2887, th, 3000, step_x, step_y }, /*ok*/ 
	{ 37, true, true, 2519, th, 3000, 2 * step_x, step_y },  /*ok*/
	{ 38, true, true, 3005, th, 3000, 0, 0 }, /*ok*/
	{ 39, true, true, 2779, th, 3000, step_x, 0 }, /*ok*/  
	{ 40, true, true, 2718, th, 3000, -step_x, -step_y }, /*ok*/
	{ 41, true, true, 2806, th, 3000, 0, -step_y }, /*ok*/
	{ 42, true, true, 2784, th, 3000, -2 * step_x, -2 * step_y }, /*ok*/
	{ 43, true, true, 2813, th, 3000, -step_x, -2 * step_y }, /*ok*/
	{ 44, true, false, 0, th, 3000, 2 * step_x, -2 * step_y }, /*ok*/
	{ 48, true, true, 2736, th, 3000, 0, 2 * step_y }, /*ok*/
	{ 49, true, true, 2229, th, 3000, step_x, 2 * step_y }, /*ok*/
	{ 50, true, true, 2303, th, 3000, -step_x, step_y }, /*ok*/
	{ 51, true, true, 2694, th, 3000, 0, step_y }, /*ok*/
	{ 52, true, true, 2890, th, 3000, -2 * step_x, 0 }, /*ok*/
	{ 53, true, true, 3064, th, 3000, -step_x, 0 }, /*ok*/
	{ 54, true, true, 2621, th, 3000, 2 * step_x, 0 }, /*ok*/
	{ 55, true, true, 2654, th, 3000, -2 * step_x, -step_y }, /*ok*/
	{ 56, true, true, 2756, th, 3000, step_x, -step_y }, /*ok*/
	{ 57, true, true, 2781, th, 3000, 2 * step_x, -step_y }, /*ok*/
	{ 58, true, true, 2735, th, 3000, 0, -2 * step_y }, /*ok*/
	{ 59, true, true, 2804, th, 3000, step_x, -2 * step_y } /*ok*/
};
//
//amp#5, V(SiPM) = 46V (spe by mean, including afterpulses)
//{
//	{ 32, true, true, 1558, 1000, 3000, -2 * step_x, 2 * step_y },
//	{ 33, true, true, 1325, 1000, 3000, -step_x, 2 * step_y },
//	{ 34, true, true, 1725, 1100, 3000, 2 * step_x, 2 * step_y },
//	{ 35, true, true, 1683, 1100, 3000, -2 * step_x, step_y },
//	{ 36, true, true, 1779, 1200, 3000, step_x, step_y },
//	{ 37, true, true, 1474, 950, 3000, 2 * step_x, step_y },
//	{ 38, true, true, 1873, 1200, 3000, 0, 0 },
//	{ 39, true, true, 1679, 1000, 3000, step_x, 0 },
//	{ 40, true, true, 1663, 1000, 3000, -step_x, -step_y },
//	{ 41, true, true, 1663, 1000, 3000, 0, -step_y },
//	{ 42, true, true, 1645, 1000, 3000, -2 * step_x, -2 * step_y },
//	{ 43, true, true, 1675, 1000, 3000, -step_x, -2 * step_y },
//	{ 44, true, false, 0, 1800, 3000, 2 * step_x, -2 * step_y },
//	{ 48, true, true, 1647, 1000, 3000, 0, 2 * step_y },
//	{ 49, true, true, 1263, 850, 3000, step_x, 2 * step_y },
//	{ 50, true, true, 1305, 900, 3000, -step_x, step_y },
//	{ 51, true, true, 1555, 1000, 3000, 0, step_y },
//	{ 52, true, true, 1792, 1100, 3000, -2 * step_x, 0 },
//	{ 53, true, true, 1916, 1300, 3000, -step_x, 0 },
//	{ 54, true, true, 1510, 1000, 3000, 2 * step_x, 0 },
//	{ 55, true, true, 1579, 1000, 3000, -2 * step_x, -step_y },
//	{ 56, true, true, 1686, 1000, 3000, step_x, -step_y },
//	{ 57, true, true, 1707, 1100, 3000, 2 * step_x, -step_y },
//	{ 58, true, true, 1659, 1100, 3000, 0, -2 * step_y },
//	{ 59, true, true, 1692, 1100, 3000, step_x, -2 * step_y }
//};
//amp#5, V(SiPM) = 48V (spe by mean, including afterpulses & x-talk);
//{
//	{ 32, true, true, 4380, 2000, 3000, -2 * step_x, 2 * step_y }, /*ok*/
//	{ 33, true, true, , 2000, 3000, -step_x, 2 * step_y },/*ok*/
//	{ 34, true, true, , 2000, 3000, 2 * step_x, 2 * step_y },/*ok*/
//	{ 35, true, true, , 2370, 3000, -2 * step_x, step_y },/*ok*/
//	{ 36, true, true, , 2000, 3000, step_x, step_y },/*ok*/
//	{ 37, true, true, , 2200, 3000, 2 * step_x, step_y },/*ok*/
//	{ 38, true, true, , 2000, 3000, 0, 0 },/*ok*/
//	{ 39, true, true, , 2300, 3000, step_x, 0 },/*ok*/
//	{ 40, true, true, , 2000, 3000, -step_x, -step_y },/*ok*/
//	{ 41, true, true, , 2350, 3000, 0, -step_y },/*ok*/
//	{ 42, true, true, , 2000, 3000, -2 * step_x, -2 * step_y },/*ok*/
//	{ 43, true, false, 0, 5000, 3000, -step_x, -2 * step_y }, /*ok*/
//	{ 44, true, false, 0, 5000, 3000, 2 * step_x, -2 * step_y },/*ok*/
//	{ 48, true, true, , 2000, 3000, 0, 2 * step_y },/*ok*/
//	{ 49, true, true, , 1900, 3000, step_x, 2 * step_y },/*ok*/
//	{ 50, true, true, , 2000, 3000, -step_x, step_y },/*ok*/
//	{ 51, true, true, , 2000, 3000, 0, step_y },/*ok*/
//	{ 52, true, true, , 2300, 3000, -2 * step_x, 0 },/*ok*/
//	{ 53, true, true, , 2300, 3000, -step_x, 0 },/*ok*/
//	{ 54, true, true, , 2000, 3000, 2 * step_x, 0 },/*ok*/
//	{ 55, true, true, , 2000, 3000, -2 * step_x, -step_y },/*ok*/
//	{ 56, true, true, , 2200, 3000, step_x, -step_y },/*ok*/
//	{ 57, true, true, , 2300, 3000, 2 * step_x, -step_y },/*ok*/
//	{ 58, true, true, , 2200, 3000, 0, -2 * step_y },/*ok*/
//	{ 59, true, true, , 2000, 3000, step_x, -2 * step_y }/*ok*/
//};
//amp#5, V(SiPM) = 49V (spe by mean, including afterpulses); th=2000 (all ch coordinates are correct)
//{
//	{ 32, true, true, 3203, 2000, 3000, -2 * step_x, 2 * step_y }, /*ok*/
//	{ 33, true, true, 2892, 2000, 3000, -step_x, 2 * step_y },/*ok*/
//	{ 34, true, true, 3530, 2000, 3000, 2 * step_x, 2 * step_y },/*ok*/
//	{ 35, true, true, 3478, 2370, 3000, -2 * step_x, step_y },/*ok*/
//	{ 36, true, true, 3452, 2000, 3000, step_x, step_y },/*ok*/
//	{ 37, true, true, 3019, 2200, 3000, 2 * step_x, step_y },/*ok*/
//	{ 38, true, true, 3688, 2000, 3000, 0, 0 },/*ok*/
//	{ 39, true, true, 3447, 2300, 3000, step_x, 0 },/*ok*/
//	{ 40, true, true, 3421, 2000, 3000, -step_x, -step_y },/*ok*/
//	{ 41, true, true, 3423, 2350, 3000, 0, -step_y },/*ok*/
//	{ 42, true, true, 3449, 2000, 3000, -2 * step_x, -2 * step_y },/*ok*/
//	{ 43, true, false, 0, 5000, 3000, -step_x, -2 * step_y }, /*ok*/
//	{ 44, true, false, 0, 5000, 3000, 2 * step_x, -2 * step_y },/*ok*/
//	{ 48, true, true, 3404, 2000, 3000, 0, 2 * step_y },/*ok*/
//	{ 49, true, true, 2767, 1900, 3000, step_x, 2 * step_y },/*ok*/
//	{ 50, true, true, 2903, 2000, 3000, -step_x, step_y },/*ok*/
//	{ 51, true, true, 3380, 2000, 3000, 0, step_y },/*ok*/
//	{ 52, true, true, 3550, 2300, 3000, -2 * step_x, 0 },/*ok*/
//	{ 53, true, true, 3638, 2300, 3000, -step_x, 0 },/*ok*/
//	{ 54, true, true, 3173, 2000, 3000, 2 * step_x, 0 },/*ok*/
//	{ 55, true, true, 3157, 2000, 3000, -2 * step_x, -step_y },/*ok*/
//	{ 56, true, true, 3484, 2200, 3000, step_x, -step_y },/*ok*/
//	{ 57, true, true, 3406, 2300, 3000, 2 * step_x, -step_y },/*ok*/
//	{ 58, true, true, 3383, 2200, 3000, 0, -2 * step_y },/*ok*/
//	{ 59, true, true, 3513, 2000, 3000, step_x, -2 * step_y }/*ok*/
//};
//amp#5, V(SiPM) = 49V (spe by mean, including afterpulses & x-talk);
//{
//	{ 32, true, true, 7485, 2000, 3000, -2 * step_x, 2 * step_y }, /*ok*/
//	{ 33, true, true, 5305, 2000, 3000, -step_x, 2 * step_y },/*ok*/
//	{ 34, true, true, 9952, 2000, 3000, 2 * step_x, 2 * step_y },/*ok*/
//	{ 35, true, true, 9425, 2370, 3000, -2 * step_x, step_y },/*ok*/
//	{ 36, true, true, 9405, 2000, 3000, step_x, step_y },/*ok*/
//	{ 37, true, true, 6340, 2200, 3000, 2 * step_x, step_y },/*ok*/
//	{ 38, true, true, 11960, 2000, 3000, 0, 0 },/*ok*/
//	{ 39, true, true, 9435, 2300, 3000, step_x, 0 },/*ok*/
//	{ 40, true, true, 12160, 2000, 3000, -step_x, -step_y },/*ok*/
//	{ 41, true, true, 10660, 2350, 3000, 0, -step_y },/*ok*/
//	{ 42, true, true, 11640, 2000, 3000, -2 * step_x, -2 * step_y },/*ok*/
//	{ 43, true, false, 0, 5000, 3000, -step_x, -2 * step_y }, /*ok*/
//	{ 44, true, false, 0, 5000, 3000, 2 * step_x, -2 * step_y },/*ok*/
//	{ 48, true, true, 8633, 2000, 3000, 0, 2 * step_y },/*ok*/
//	{ 49, true, true, 4856, 1900, 3000, step_x, 2 * step_y },/*ok*/
//	{ 50, true, true, 5049, 2000, 3000, -step_x, step_y },/*ok*/
//	{ 51, true, true, 7643, 2000, 3000, 0, step_y },/*ok*/
//	{ 52, true, true, 9446, 2300, 3000, -2 * step_x, 0 },/*ok*/
//	{ 53, true, true, 11930, 2300, 3000, -step_x, 0 },/*ok*/
//	{ 54, true, true, 7342, 2000, 3000, 2 * step_x, 0 },/*ok*/
//	{ 55, true, true, 9197, 2000, 3000, -2 * step_x, -step_y },/*ok*/
//	{ 56, true, true, 9796, 2200, 3000, step_x, -step_y },/*ok*/
//	{ 57, true, true, 10860, 2300, 3000, 2 * step_x, -step_y },/*ok*/
//	{ 58, true, true, 10020, 2200, 3000, 0, -2 * step_y },/*ok*/
//	{ 59, true, true, 10970, 2000, 3000, step_x, -2 * step_y }/*ok*/
//};




//ChCharacteristics::~ChCharacteristics()
//{
//}

vector<ChCharacteristicsStruct>& ChCharacteristics::GetChCharacteristics()
{
	return ch_characteristics_struct;
}
