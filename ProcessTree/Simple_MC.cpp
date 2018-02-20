#include "Simple_MC.h"

using namespace std;

Simple_MC::Simple_MC(TGraph2D* gr2D, bool is_draw, int N_runs) : gr2D(gr2D), is_draw(is_draw), N_runs(N_runs)
{
	h_x = 0; // диаметр источника [mm]
	h_c = 6;//14.3 or 6 
	l_x = 14.8;
	lambda_bar = 17.2;

	ostringstream oss;
	oss << path_name_tree << "MC_results.txt";
	file_out.open(oss.str().c_str());


	N_ch = 25;

	PMMA_width = 3;
	LAr_dead_width = 2;
	THGEM_Cathode_width = 0.5;
	Al_window_width = 23;

	x_center_shift = 0;
	y_center_shift = 0;

	h2D = new TH2D("h2D", "h2D", 1000, -55, 55, 1000, -55, 55);
	h2D = gr2D->GetHistogram();
}


Simple_MC::~Simple_MC()
{
}

void Simple_MC::Calc_MC()
{
	for (int i_tmp = -50; i_tmp < 50; i_tmp++)
	{
		cout << i_tmp << "; " << h2D->Interpolate(i_tmp, 20) << "; " << gr2D->Interpolate(i_tmp, 20) << endl;
	}
	
	
	for (int i_runs = 0; i_runs < N_runs; i_runs++)
	{
		cout << "Run = " << i_runs << endl;

		// глубина поглощения в LAr гамма квантов [mm]
		while (true)
		{
			lambda = rnd3.Exp(lambda_bar);
			if (lambda < 50)
				break;
		}
			
		double l_L = lambda + PMMA_width + LAr_dead_width + THGEM_Cathode_width + Al_window_width; // расстояние от коллиматора до экрана [mm] 
		
		double h_s = (l_L + l_x * h_c / (h_c + h_x)) / (l_x / (h_c + h_x)); //ожидаемый диаметр пятна
		//cout << "h_s = " << h_s << endl;
		double radius = h_s / 2.0;

		double x_source;
		double y_source;
		while (true)
		{
			double x_tmp = (rnd3.Uniform() - 0.5) * 2 * radius;
			double y_tmp = (rnd3.Uniform() - 0.5) * 2 * radius;
			if (x_tmp*x_tmp + y_tmp*y_tmp < (radius)*(radius))
			{
				x_source = x_tmp;
				y_source = y_tmp;
				break;
			}
		}
		////test
		//x_source = 0;
		//y_source = 0;

		vector<double> n_pe;
		vector<double> x_position;
		vector<double> y_position;
		n_pe.resize(N_ch);
		x_position.resize(N_ch);
		y_position.resize(N_ch);

		double x_cog = 0;
		double y_cog = 0;
		double n_pe_summ = 0;
		//cog

		//set N_pe in each ch by integrating 2D distribution
		for (int i = 0; i < N_ch; i++)
		{
			int ch = GetChIdSiPMCorrect(i);

			for (int j = 0; j < ChCharacteristics::GetChCharacteristics().size(); j++)
			{
				if (ChCharacteristics::GetChCharacteristics()[j].ch_id == ch)
				{
					double x_SiPM = ChCharacteristics::GetChCharacteristics()[j].x_position;
					double y_SiPM = ChCharacteristics::GetChCharacteristics()[j].y_position;
					double integral = 0;
					double SiPM_size = 6;
					int N_points_per_axis = 100;
					double integration_step = SiPM_size / (N_points_per_axis);

					double x;
					double y;
					for (int i_x = 0; i_x < N_points_per_axis; i_x++)
					{
						x = i_x * integration_step - SiPM_size / 2.0;
						for (int i_y = 0; i_y < N_points_per_axis; i_y++)
						{
							y = i_y * integration_step - SiPM_size / 2.0;

							//chose area only inside LxL mm^2 area
							double x_tmp = x + x_SiPM - x_source + x_center_shift;
							double y_tmp = y + y_SiPM - y_source + y_center_shift;
							double L = 23;
							if (abs(x_tmp) < L && abs(y_tmp) < L)
							{
								integral += h2D->Interpolate(x_tmp, y_tmp);
							}

						}
					}
					n_pe[i] = integral * integration_step * integration_step;
					x_position[i] = x_SiPM;
					y_position[i] = y_SiPM;

					x_cog += n_pe[i] * ChCharacteristics::GetChCharacteristics()[j].x_position;
					y_cog += n_pe[i] * ChCharacteristics::GetChCharacteristics()[j].y_position;
					n_pe_summ += n_pe[i];
					//cout << x << "\t" << y << "\t" << n_pe[i] << endl;
					break;
				}
			}
		}

		if (n_pe_summ == 0)
		{
			cout << "n_pe_summ == 0" << endl;
			//system("pause");
			//exit(1);
		}
		else
		{
			x_cog /= n_pe_summ;
			y_cog /= n_pe_summ;
			file_out << x_source << "\t" << y_source << "\t" << x_cog << "\t" << y_cog << "\t" << n_pe_summ << endl;
		}


		if (is_draw)
		{		
			//show TGraph2D
			TGraph2D* gr2D_shift = new TGraph2D(N_ch, &x_position[0], &y_position[0], &n_pe[0]);
			TH2D *h = new TH2D("h", "", 1000, -50, 50, 1000, -50, 50);
			g()->c->cd(2);
			// method to change range	
			// https://root-forum.cern.ch/t/tgraph2d-access-xyz-range-and-title-out-of-sync-color-bar/15722
			// "TGraph2D: access xyz range and title, out of sync color bar"
			gr2D_shift->SetHistogram(h);
			gr2D_shift->Draw("TRI1");
		}

		//cout << x_source << "\t" << y_source << endl;

	}

	//system("pause");
}

void Simple_MC::Calc_center_shift()
{
	double n_pe_summ = 0;
	x_center_shift = 0;
	y_center_shift = 0;
	for (int i = 0; i < N_ch; i++)
	{
		int ch = GetChIdSiPMCorrect(i);

		for (int j = 0; j < ChCharacteristics::GetChCharacteristics().size(); j++)
		{
			if (ChCharacteristics::GetChCharacteristics()[j].ch_id == ch)
			{
				double x = ChCharacteristics::GetChCharacteristics()[j].x_position;
				double y = ChCharacteristics::GetChCharacteristics()[j].y_position;
				double n_pe = gr2D->Interpolate(x, y);
				x_center_shift += n_pe * x;
				y_center_shift += n_pe * y;
				n_pe_summ += n_pe;
				break;
			}			
		}
	}

	if (n_pe_summ > 0)
	{
		x_center_shift /= n_pe_summ;
		y_center_shift /= n_pe_summ;
	}

	cout << "x_center_shift = " << x_center_shift << "; y_center_shift = " << y_center_shift << endl;
}