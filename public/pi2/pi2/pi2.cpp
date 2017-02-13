// pi2.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "data.h"
#include "Option_euro.h"
using namespace std;


int main()
{
	string x;
	//test sur 1 donnée d'une option
	Data re(100.0,100.0,0.05,1.0,2.5);
	double init = 0.3;  // Our guess impl. vol of 30%
	double epsilon = 0.001;


	cout << "BSC : " << re.BlackScholespriceCall(0.05) << endl;
	cout << "Vega : " << re.vega(0.05) << endl;
	cout << "Newton raphson : " << re.newton_raphson(re.BlackScholespriceCall(0.05), epsilon, 0) << endl;
	getline(cin, x);
	return 0;
}

