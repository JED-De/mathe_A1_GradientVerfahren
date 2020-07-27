#include <iostream>
#include <math.h>
#include "CMyVektor.h"
using namespace std;

/*
int main() {


	vector<double> ev = { 0.2,-2.1 };
	CMyVektor test1(ev);
	GVM(test1, f, 1);
	ev = { 0,0,0 };
	CMyVektor test2(ev);
	GVM(test2, g, 0.1);
	system("pause");
	return 0;
}
*/
int main() {


	vector<double> e = { 0.2,-2.1 };
	CMyVektor test1(e);
	//gradientverfahren(1,test1, f);
	e = { 0,0,0 };
	CMyVektor test2(e);
	gradientverfahren(0.1, test2, g);
	system("pause");
	return 0;
}
