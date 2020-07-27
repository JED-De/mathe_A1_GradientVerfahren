#pragma once
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

const double h = pow(10, -8);

class CMyVektor {
private:
	vector<double> vektor;

public:
	CMyVektor();

	CMyVektor(int size);

	CMyVektor(vector<double> vektor);

	int getDimension();

	void setKomponent(int line, double key);

	double getKomponent(int line);

	double laenge();

	void Komponent();
};

CMyVektor gradient(CMyVektor x, double(*function)(CMyVektor x));
CMyVektor operator+(CMyVektor& a, CMyVektor& b);
CMyVektor operator*(double lambda, CMyVektor a);
double f(CMyVektor vektor);
double g(CMyVektor vektor);
void gradientverfahren(double lambda, CMyVektor vektor, double(*function)(CMyVektor x));