double func_x(double x)
{
	double y;
	
	double a1 = 13.96288;
	double b1 = 1.99177;
	double p1 = -15.08618;
	
	double a2 = -13.78934;
	double b2 = 1.96805;
	double p2 = 14.93198;
	
	double A = -0.1873;
	double B = 1.01108;

	if(x < p1)
	{
		y = a1 + x*b1;
	}
	else if(x > p2)
	{
		y = a2 + x*b2;
	}
	else
	{
		y = A + x*B;
	}
	
	
	return y;
}

//#include "Math/Polynomial.h"
#include "TMath.h"
#include "Math/Interpolator.h"


void code()
{
	gSystem->Load("libMathMore");
	
	double x, y;
	
	ifstream file_data("D:\\git_repositories\\Parser_signal_finder_v2\\root_scripts\\YAP_Ce_rel_662keV.dat"); 	
	vector<double> Ev;
	vector<double> Nonpropv;
	while (file_data.good()) 
	{
		file_data >> x >> y;
		Ev.push_back(x);
		Nonpropv.push_back(y);
  	}
	ROOT::Math::Interpolator inter(Ev.size(), ROOT::Math::Interpolation::kLINEAR);
	inter.SetData(Ev, Nonpropv);
	
	
	ifstream file_in("D:\\git_repositories\\Parser_signal_finder_v2\\root_scripts\\input.dat");
	vector<double> E2v;
	vector<double> Countsv;
	while (file_in.good()) 
	{
		file_in >> x >> y;
		E2v.push_back(x);
		Countsv.push_back(y);
  	}	
	
	
	
	
	ofstream file_out("D:\\git_repositories\\Parser_signal_finder_v2\\root_scripts\\output.dat"); 	
	for(int i = 0; i < E2v.size(); i++)
	{		
		file_out << inter.Eval(E2v[i])*E2v[i] << endl;		
	}
	
}