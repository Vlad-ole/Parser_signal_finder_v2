#include "Interpolate2D.h"

//#include <Eigen/Dense>

//using Eigen::MatrixXd;

Interpolate2D::Interpolate2D(TGraph2D* gr2d) : gr2d(gr2d)
{
}

Interpolate2D::Interpolate2D()
{
}

double Interpolate2D::GetValueLine(double x, double y)
{
	return gr2d->Interpolate(x, y);//dummy
}

double Interpolate2D::GetValueBicubic(double x, double y)
{
	double result = 0;
	double a_matrix[4][4];

	//result = 

	//MatrixXd m(2, 2);
	//m(0, 0) = 3;
	//m(1, 0) = 2.5;
	//m(0, 1) = -1;
	//m(1, 1) = m(1, 0) + m(0, 1);
	//std::cout << m << std::endl;
	
	return result;
}


Interpolate2D::~Interpolate2D()
{
}
