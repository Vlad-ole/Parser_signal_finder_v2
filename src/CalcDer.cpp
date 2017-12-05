#include "CalcDer.h"

using namespace std;

vector<bool> CalcDer::is_first_obj({ true, true });
vector<vector<double> > CalcDer::C_i_der(2);

CalcDer::CalcDer(std::vector<double> yv, const int param_n_points, const int order_of_derivative)
{
	const int n_points = yv.size();
	yv_der.resize(n_points);

	//well, I do not know  how to write this part correctly
	//What should I do if I have different param_n_points for the same order_of_derivative?
	//if (is_first_obj[order_of_derivative])
	//{
	//	is_first_obj[order_of_derivative] = false;
	//	CalculateCoeffDer(param_n_points, order_of_derivative);
	//}

	//simple variant
	C_i_der[0].clear();
	C_i_der[1].clear();
	CalculateCoeffDer(param_n_points, order_of_derivative);

	const int point_half = (param_n_points - 1) / 2.0;

//#pragma omp parallel for num_threads(4) //If you create threads during each event this can slow down you prog. Be accurately!
	for (int i = 0; i < yv.size(); i++)
	{

		//if (i < point_half || i >(yv.size() - point_half - 1))
		//{
		//	yv_der[i] = 0;//this works good only if you use signal without baseline
		//}
		if (i < point_half) 
		{
			//yv_der[i] = yv[point_half];
		}
		else if ( i > (yv.size() - point_half - 1) )
		{
			//yv_der[i] = yv[yv.size() - 1];
		}
		else
		{
			double value = 0;
			for (int j = 0; j < C_i_der[order_of_derivative].size(); j++)
			{
				value += C_i_der[order_of_derivative][j] * yv[i - point_half + j];
			}
			yv_der[i] = value;
		}
	}

	double yv_der_avr_left = 0;
	const int n_points_to_avr = 5;
	for (int i = point_half; i < (point_half + n_points_to_avr); i++)
	{
		yv_der_avr_left += yv_der[i];
	}
	yv_der_avr_left /= n_points_to_avr;


	double yv_der_avr_right = 0;
	for (int i = (yv.size() - point_half - 1 - n_points_to_avr); i < (yv.size() - point_half - 1); i++)
	{
		yv_der_avr_right += yv_der[i];
	}
	yv_der_avr_right /= n_points_to_avr;



	for (int i = 0; i < point_half; i++)
	{
		yv_der[i] = yv_der_avr_left;
	}

	for (int i = (yv.size() - point_half/* - 1 + 1*/); i < yv.size(); i++)
	{
		yv_der[i] = yv_der_avr_right;
	}

}


CalcDer::~CalcDer()
{
}

std::vector<double> CalcDer::GetDer()
{
	return yv_der;
}

void CalcDer::CalculateCoeffDer(int points, const int order_of_derivative)
{
	//Savitzky–Golay filter
	//order = 3

	const int m = points;

	//ïîñ÷èòàòü êîýôôèöèåíòû  C_i
	switch (order_of_derivative)
	{
		case 0:
		{
			for (int i = (1 - m) / 2.0; i <= (m - 1) / 2.0; i++)
			{
				double numerator = (3 * pow(m, 2.0) - 7 - 20 * pow(i, 2.0)) / 4.0;
				double denominator = m * (pow(m, 2.0) - 4) / 3.0;
				C_i_der[order_of_derivative].push_back(numerator / denominator);
			}
			//cout << "it was initialized values for 0 order_of_derivative" << endl;
			break;
		}
		case 1:
		{
			for (int i = (1 - m) / 2.0; i <= (m - 1) / 2.0; i++)
			{
				double numerator = 5 * (3 * pow(m, 4.0) - 18 * pow(m, 2.0) + 31)*i - 28 * (3 * pow(m, 2.0) - 7)*pow(i, 3.0);
				double denominator = m * (pow(m, 2.0) - 1) * (3 * pow(m, 4.0) - 39 * pow(m, 2.0) + 108) / 15.0;
				C_i_der[order_of_derivative].push_back(numerator / denominator);
			}
			//cout << "it was initialized values for 1 order_of_derivative" << endl;
			break;
		}
		default:
		{
			cout << "you should enter the order_of_derivative" << endl;
			system("pause");
			exit(1);
			break;
		}
	}


}
