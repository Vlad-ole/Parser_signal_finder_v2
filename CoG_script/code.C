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


void code()
{
	ifstream file_in("D:\\git_repositories\\Parser_signal_finder_v2\\CoG_script\\xy_no_MC.txt"); 	
	
	
	double x, y;
	vector<double> xv;
	vector<double> yv;
	while (file_in.good()) 
	{
		file_in >> x >> y;
		xv.push_back(x);
		yv.push_back(y);
  	}
	
	
	ofstream file_out("D:\\git_repositories\\Parser_signal_finder_v2\\CoG_script\\xy_MC.txt"); 
	
	for(int i = 0; i < xv.size(); i++)
	{
		
		file_out << func_x(xv[i]) << endl;
		
	}
	
}