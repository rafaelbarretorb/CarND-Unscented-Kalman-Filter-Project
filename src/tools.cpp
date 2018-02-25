#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}


VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations, const vector<VectorXd> &ground_truth)
{
    /**
  TODO:
    * Calculate the RMSE here.
  */
	VectorXd rmse(4);
	rmse << 0,0,0,0;

	VectorXd residual;
	if (estimations.size() != ground_truth.size() || estimations.size()==0)
	{
		cout << "ERROR RMSE" << endl;
		cout << estimations.size() << endl;
		
		return rmse;
	}

	for(unsigned int i=0; i < estimations.size(); ++i)
	{
		VectorXd residual;
		residual = estimations[i] - ground_truth[i];
		residual = residual.array()*residual.array();
		rmse += residual;

	}
    
	//calculate the mean
	rmse = rmse/(estimations.size());

	//calculate the squared root
	rmse = (rmse.array()).sqrt();

	//return the result
	cout << "RMSE = ["<< rmse(0) << " , "<< rmse(1) << " , "<< rmse(2)<< " , " << rmse(3) << "]" << endl;
	cout << estimations.size() << endl;
	return rmse;
}

VectorXd Tools::Conversion_Polar2Cartesian(const VectorXd &z)
{
	VectorXd z_radar_cartesian;

	float phi;
	phi = Tools::AngleNorm(phi);

	z_radar_cartesian(0) = cos(phi)*z(0);
	z_radar_cartesian(1) = sin(phi)*z(0);      
	

	return z_radar_cartesian;
}

float Tools::AngleNorm(const float &phi)
{
	float phi_norm = phi;
	PI = 3.14159265358979;

	while(phi_norm > PI)
        phi_norm -= 2*PI;

    while(phi_norm <-PI)
        phi_norm += 2*PI;

	return phi_norm;
}
