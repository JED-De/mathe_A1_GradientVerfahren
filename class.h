#include<iostream>
#include<math.h>
#include<vector>
#include<string>
using namespace std;

// Aufgabe 1
class CMyVektor
{
private:
	vector<double> vek;

public:
	// einen Vektor einer bestimmten Dimension anzulegen
	CMyVektor() 
	{
		vek = {};
	}

	CMyVektor(int size) {
		vek.resize(size);
	}

	CMyVektor(vector<double> vektor) {
		vek = vektor;
	}
	// die Dimension eines Vektors 
	int getDimension() const { return vek.size(); };

	// eine bestimmte Komponente des Vektor zu setzen
	void setKomponent(int pos, double wert)
	{
		vek.at(pos) = wert;
	};

	// eine bestimmte Komponente des Vektors zurückgeben
	double getKomponent(int pos)
	{
		return vek.at(pos);
	}
	

	// laenge des Vektors zu bestimmen
	double laenge()
	{
		double tmp = 0.0, laenge = 0.0;
		for (int i = 0; i < getDimension(); i++)
		{
			tmp = vek.at(i) * vek.at(i);
			laenge += tmp;
		}
		laenge = sqrt(laenge);
		return laenge;
	}

	string Komponent()
	{
		string ausgabe;
		ausgabe += "( ";
		for (int i = 0; i < vek.size(); i++)
		{
			ausgabe += to_string((double)vek.at(i)) + " , ";
		}
		ausgabe += to_string((double)vek.at(vek.size()-1)) + ")";
		//ausgabe += " )";
		return ausgabe;
	}
};


CMyVektor operator+(CMyVektor a, CMyVektor b)
{
	CMyVektor sum(a.getDimension());
	double ausgabe;
	for (int i = 0; i < a.getDimension(); i++)
	{
		ausgabe = a.getKomponent(i) + b.getKomponent(i);
		sum.setKomponent(i, ausgabe);
	}
	return sum;
};
CMyVektor operator*(double lambda, CMyVektor a)
{
	CMyVektor mult(a.getDimension());
	double ausgabe;
	for (int i = 0; i < a.getDimension(); i++)
	{
		ausgabe = lambda * a.getKomponent(i);
		mult.setKomponent(i, ausgabe);
	}
	return mult;
};

//AUFGABE 2
CMyVektor gradient(CMyVektor x, double(*funktion)(CMyVektor x))
{
	long double h = 1e-8;
	CMyVektor gradient(x.getDimension());
	for (int i = 0; i < x.getKomponent(i) + h; i++)
	{
		CMyVektor tmp = x;
		tmp.setKomponent(i, x.getKomponent(i) + h);
		tmp.setKomponent(i, x.getKomponent(i));
	}
	return gradient;
}

// AUFGABE 3

CMyVektor GVM(CMyVektor x, double(*funktion)(CMyVektor x), double lambda)
{
	CMyVektor x_neu(x.getDimension());
	CMyVektor x_test(x.getDimension());
	int schritt = 0;
	double fx_neu, fx, fx_test, neulamb = 0;
	CMyVektor grad = gradient(x, funktion);
	for (int i = 0; i < 25 && grad.laenge() >= 1e-5; i++)
	{

		CMyVektor grad = gradient (x, funktion);

		fx = funktion(x);

		cout << "schritt " << i << ":" << endl;
		cout << "       x = (" << x.Komponent() << ")" << endl;
		cout << "       lambda = " << lambda << endl;
		cout << "       f(x) = " << fx << endl;
		cout << "       grad f(x) = (" << grad.Komponent() << ")" << endl;
		cout << "       ||grad f(x) || = " << grad.laenge() << endl << endl;

		x_neu = x + lambda * gradient(x, funktion);
		fx_neu = funktion(x_neu);

		cout << "      x_neu = (" << x_neu.Komponent() << ")" << endl;
		cout << "      f(x_neu) = (" << fx_neu << endl << endl;

		if (fx_neu > fx)
		{
			//lambda = 2 * lambda
			x_test = x + 2 * lambda * gradient(x, funktion);

			cout << "       Test mit doppelter Schrittweite ( lambda = " << 2 * lambda << "):" << endl;
			cout << "       x_test (" << x_test.Komponent() << ")" << endl;
			fx_test = funktion(x_test);
			cout << "       f(x_test) = " << fx_test << endl;

			if (fx_test < fx_neu)
			{
				x = x_test;
				cout << "      verdoppele Schrittweite!" << endl << endl;
				lambda = 2 * lambda;

			}
			else {
				x = x_neu;
				cout << "      behalte alte Schrittweite!" << endl << endl;
			}

		}
		else if (fx_neu <= fx)
		{
			do {
				lambda = lambda / 2;
				x_neu = x + lambda * gradient(x, funktion);
				fx_neu = funktion(x_neu);
				cout << "      halbiere Schrittweite (lambda = " << lambda << "):" << endl;
				cout << "      x_neu (" << x_neu.Komponent() << ")" << endl;
				cout << "      f(x_neu) = " << fx_neu << endl << endl;

			} while (fx_neu < fx);

			x = x_neu;
		}
		if (gradient(x, funktion).laenge() < 1e-5)
		{
			cout << "Ende Wegen ||grad f(x)|| < 1e-5 bei" << endl;
			cout << "         x = (" << x.Komponent() << endl;
			cout << "         lambda = " << lambda << endl;
			cout << "         f(x) = " << fx << endl;
			cout << "         grad f(x)= (" << gradient(x, funktion).Komponent() << ")" << endl;
			cout << "         ||grad f(x)|| = " << gradient(x, funktion).laenge() << endl << endl;
			break;
		}
		else if (i + 1 == 25)
		{
			cout << "Ende Wegen Schrittanzahl = 25 bei " << endl;
			cout << "        x = (" << x.Komponent() << endl;
			cout << "        lambda = " << lambda << endl;
			cout << "        f(x) = " << fx << endl;
			cout << "        ||grad f(x)|| = " << gradient(x, funktion).laenge() << endl << endl;
			break;
		}

	}
	return x;
}

/*
CMyVektor GVM(CMyVektor x, double(*funktion)(CMyVektor x), double lambda)
{
	CMyVektor x_start = x;
	CMyVektor x_neu = x_start;
	CMyVektor x_alt = x;
	CMyVektor x_test(x.getDimension());
	int Schritt = 0;
	CMyVektor grad(x.getDimension());
	if (lambda == 0.0) // Default Lambda
	{
		lambda = 1.0;
	}

	while (true)
	{
		x_alt = x_neu;

		if (grad.laenge() < pow(10, -5))
		{
			cout << "Ende wegen ||gradf(x)|| < 1e-5 bei" << endl;
		}
		else if (Schritt >= 25)
		{
			cout << "Ende wegen Schrittanzahl = 25 bei" << endl;
		}
		else
		{
			cout << "Schritt " << Schritt << endl;
		}
		cout << "        x = "; x_alt.Komponent();
		cout << "        lambda = " << lambda << endl;

		CMyVektor tmp = lambda * gradient(x_alt, funktion);
		x_neu = x_alt + tmp;

		cout << "       f(x) = " << funktion(x_alt) << endl;
		cout << "       grad f(x) = (" << grad.Komponent() << ")" << endl;

		cout << "       x = (" << x.Komponent() << ")" << endl;
		cout << "       lambda = " << lambda << endl;
		
		cout << "       ||grad f(x)|| = " << grad.laenge() << endl << endl;

		if (funktion(x_neu) > funktion(x))
		{
			x_test = x_alt + 2 * lambda * grad;

			////////////////////////////
			cout << "        Test mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl;
			cout << "        x_test = ";
			x_test.Komponent();
			cout << "        f(x_Test) = " << funktion(x_test) << endl;

			
			if (funktion(x_test) > funktion(x_neu))
			{
				x_alt = x_test;
				lambda *= 2;
				cout << "        verdoppele Schrittweite!" << endl << endl;
			}
			else
			{
				cout << "        Behalte alte Schrittweite!" << endl << endl;
				x_alt = x_neu;
			}
		}
		else if (funktion(x_neu) <= funktion(x))
		{
			while (funktion(x_neu) > funktion(x_alt))
			{
				lambda /= 2;
			}
		
			cout << "        halbiere Schrittweite (lambda = " << lambda << "):" << endl;
			CMyVektor tmp = lambda * grad;
			x_alt = x_neu + tmp;

			cout << "        x_neu = ";
			x_neu.Komponent();

			cout << "        f(x_neu) = " << funktion(x_neu) << endl << endl;
		}
		Schritt++;
	}
}
*/

	double f(CMyVektor vektor) 
	{
		double x = vektor.getKomponent(0);
		double y = vektor.getKomponent(1);
		return (sin(x * y) + sin(x) + cos(y));
	}

	double g(CMyVektor vektor) 
	{
		double x1 = vektor.getKomponent(0);
		double x2 = vektor.getKomponent(1);
		double x3 = vektor.getKomponent(2);
		return -1 * ((2 * pow(x1, 2)) - (2 * x1 * x2) + pow(x2, 2) + pow(x3, 2) - (2 * x1) - (4 * x3));
	}