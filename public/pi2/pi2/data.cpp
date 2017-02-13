#pragma once
#include "stdafx.h"
#include "data.h"
#include <iostream>
#include <cmath>
using namespace std;

Data::Data(double _S, double _K, double _R, double _T, double _P) {
	S = _S;
	K = _K;
	R = _R;
	T = _T;
	P = _P;
}

Data::Data(const Data &G) {
	S = G.S;
	K = G.K;
	R = G.R;
	T = G.T;
	P = G.P;
}

Data::~Data() {
}

double Data::GetS() {
	return S;
}

double Data::GetK() {
	return K;
}

double Data::GetR() {
	return R;
}

double Data::GetT() {
	return T;
}

double Data::GetP() {
	return P;
}

// Standard normal probability density function
double Data::norm_pdf(const double x) {
	return (1.0 / (pow(2 * 3.141592, 0.5)))*exp(-0.5*x*x);
}

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function
double Data::norm_cdf(const double x) {
	double k = 1.0 / (1.0 + 0.2316419*x);
	double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

	if (x >= 0.0) {
		return (1.0 - (1.0 / (pow(2 * 3.141592, 0.5)))*exp(-0.5*x*x) * k_sum);
	}
	else {
		return 1.0 - norm_cdf(-x);
	}
}

// Calculate the European vanilla call vega 'Greek' based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double Data::vega(const double sigma) {
	return S * sqrt(T) * norm_pdf((log(S / K) + (R + sigma*sigma / 2)*T) / (sigma*sqrt(T)));
}
//actualised price
double Data::BlackScholespriceCall(double sigma) {
	if (S<1.e-14)return 0; // check if asset worthless
	if (sigma<1.e-14) // check if sigma zero
	{
		if (S<K*exp(-R*(T)))return 0;
		else return S - K*exp(-R*(T));
	}
	if (fabs(T)<1.e-14) // check if we are at maturity
	{
		if (S<K)return 0.;
		else return S - K;
	}
	// calculate option price
	double d1 = (log(S / K) + (R + sigma*sigma / 2)*T) / (sigma*sqrt(T));
	double d2 = (log(S / K) + (R - sigma*sigma / 2)*T) / (sigma*sqrt(T));
	P = S*exp(-R*T)*norm_pdf(d1) - K*exp(-R*T)*norm_pdf(d2);
	return P;
}

double Data::BlackScholespricePut(double sigma) {
	if (S<1.e-14)return 0; // check if asset worthless
	if (sigma<1.e-14) // check if sigma zero
	{
		if (S<K*exp(-R*(T)))return 0;
		else return S - K*exp(-R*(T));
	}
	if (fabs(T)<1.e-14) // check if we are at maturity
	{
		if (S<K)return 0.;
		else return S - K;
	}
	// calculate option price
	double d1 = (log(S / K) + (R + sigma*sigma / 2)*T) / (sigma*sqrt(T));
	double d2 = (log(S / K) + (R - sigma*sigma / 2)*T) / (sigma*sqrt(T));
	P = K*exp(-R*T)*norm_pdf(-d2) - S*exp(-R*T)*norm_pdf(-d1);
	return P;
}

double Data::option_vega(double sigma){
	return vega(sigma);
}
double Data::option_price(double sigma) {
	return BlackScholespriceCall(sigma);
}

double Data::newton_raphson(double init,double epsilon,double estimation) {
	double fx = option_price(init);
	double fx1 = option_vega(init);
	if (init-estimation>epsilon) {
		estimation = init;
		init = estimation - (fx / fx1);
		newton_raphson(init, epsilon, estimation);
	}
	else {
		return init;
	}
	return init;
}



