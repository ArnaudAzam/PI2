#pragma once
#include "stdafx.h"
using namespace std;

class Data
{
private:
	double S;// Underlying asset price
	double K;// Strike price
	double R;// Risk-free rate
	double T;// Time to maturity in year
	double P;// Option market price


public:
	Data(double, double, double, double, double);
	Data(const Data&);
	~Data();
	//acessors
	double GetS();
	double GetR();
	double GetK();
	double GetT();
	double GetP();
	//mutateurs
	//functions membres
	double norm_pdf(const double x);
	double norm_cdf(const double x);
	double vega(const double);
	double BlackScholespriceCall(double sigma);
	double BlackScholespricePut(double sigma);
	double option_vega(double sigma);//for NR computations
	double option_price(double sigma);//for NR computations
	double newton_raphson(double,double,double);
	double bissection(double, double, double,double);
};