#include "CMyVektor.h"

CMyVektor::CMyVektor() {
	this->vektor = {};
}
CMyVektor::CMyVektor(int size) {
	this->vektor.resize(size);
}

CMyVektor::CMyVektor(vector<double> vektor) {
	this->vektor = vektor;
}

int CMyVektor::getDimension() {
	return vektor.size();
}

void CMyVektor::setKomponent(int line, double key) {
	this->vektor[line] = key;
}

double CMyVektor::getKomponent(int line) {
	return this->vektor[line];
}

double CMyVektor::laenge() {
	double total = 0;
	for (int i = 0; i < this->vektor.size(); i++) {
		total += this->vektor[i] * this->vektor[i];
	}
	return sqrt(total);
}

void CMyVektor::Komponent() {
	cout << "( ";
	int i = 0;
	while (i < vektor.size()) {
		cout << vektor[i] << "; ";
		i++;
	}
	cout << ")" << endl;
}

CMyVektor gradient(CMyVektor x, double(*function)(CMyVektor x)) {
	CMyVektor endresult(x.getDimension());
	CMyVektor xplush = x;

	for (int i = 0; i < x.getDimension(); i++) {
		xplush.setKomponent(i, x.getKomponent(i) + h);

		double fx = ((function(xplush) - function(x)) / h);
		endresult.setKomponent(i, fx);
		xplush = x;
	}
	return endresult;
}
CMyVektor operator+(CMyVektor & a, CMyVektor & b) {
	CMyVektor c(a.getDimension());
	if (a.getDimension() == b.getDimension()) {
		for (int i = 0; i < a.getDimension(); i++) {
			double res = (a.getKomponent(i) + b.getKomponent(i));
			c.setKomponent(i, res);
		}
	}
	return c;
}
CMyVektor operator*(double lambda, CMyVektor a) {
	CMyVektor c(a.getDimension());
	if (a.getDimension() != 0) {
		for (int i = 0; i < a.getDimension(); i++) {
			c.setKomponent(i, a.getKomponent(i) * lambda);
		}
	}
	return c;
}

double f(CMyVektor vektor) {
	double x = vektor.getKomponent(0);
	double y = vektor.getKomponent(1);
	return (sin(x * y) + sin(x) + cos(y));
}

double g(CMyVektor vektor) {
	double x1 = vektor.getKomponent(0);
	double x2 = vektor.getKomponent(1);
	double x3 = vektor.getKomponent(2);
	return -1 * ((2 * pow(x1, 2)) - (2 * x1 * x2) + pow(x2, 2) + pow(x3, 2) - (2 * x1) - (4 * x3));
}


void gradientverfahren(double lambda, CMyVektor vektor, double(*function)(CMyVektor x)) {

	CMyVektor vektorStart = vektor;
	CMyVektor vektorNew = vektorStart;
	CMyVektor vektorOld = vektor;
	CMyVektor vektorTest(vektor.getDimension());

	int schritte = 0;
	double j = gradient(vektorOld, function).laenge();
	while (true) {


		vektorOld = vektorNew;


		///////////////////////////////////////
		if (gradient(vektorOld, function).laenge() < pow(10, -5)) {
			cout << "Ende wegen ||gradf(x)|| <1e-5 bei" << endl;
		}
		else if (schritte >= 25) {
			cout << "Ende wegen Schrittanzahl = 25 bei" << endl;
		}
		else {
			cout << "Schritt " << schritte << endl;
		}
		cout << "        x = "; vektorOld.Komponent();


		cout << "        lambda = " << lambda << endl;
		///////////////////////////////////////

		CMyVektor tmp = lambda * gradient(vektorOld, function);
		vektorNew = vektorOld + tmp;

		/////////////////////////////
		cout << "        f(x) = " << function(vektorOld) << endl;
		cout << "        grad f(x) = ";
		gradient(vektorOld, function).Komponent();

		cout << "        ||grad f(x)|| = " << gradient(vektorOld, function).laenge() << endl << endl;
		///////////////////////////////

		if (gradient(vektorOld, function).laenge() < pow(10, -5) || schritte >= 25)break;

		///////////////////////////////
		cout << "        x_neu = ";
		vektorNew.Komponent();

		cout << "        f(x_neu) = " << function(vektorNew) << endl << endl;
		///////////////////////////////

		if (function(vektorNew) > function(vektorOld)) {
			CMyVektor tmp = (2 * lambda) * gradient(vektorOld, function);
			vektorTest = vektorOld + tmp;

			////////////////////////////
			cout << "        Test mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl;
			cout << "        x_test = ";
			vektorTest.Komponent();
			cout << "        f(x_Test) = " << function(vektorTest) << endl;

			/////////////////////////

			if (function(vektorTest) > function(vektorNew)) {
				vektorNew = vektorTest;
				lambda *= 2;
				cout << "        verdoppele Schrittweite!" << endl << endl;
			}
			else {
				cout << "        Behalte alte Schrittweite!" << endl << endl;
			}

		}
		else if (function(vektorNew) <= function(vektorOld)) {

			while (function(vektorNew) < function(vektorOld)) {
				lambda = lambda / 2;
				cout << "        halbiere Schrittweite (lambda = " << lambda << "):" << endl;
				CMyVektor tmp = lambda * gradient(vektorOld, function);
				vektorNew = vektorOld + tmp;

				cout << "        x_neu = ";
				vektorNew.Komponent();

				cout << "        f(x_neu) = " << function(vektorNew) << endl << endl;
			}

		}



		schritte++;
	}
}