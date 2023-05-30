#include <iostream>
using namespace std;

class Complex
{
private:
	double real;
	double image;
public:
	Complex() { real = image = 0; }
	Complex(double r, double im) { real = r; image = im; }
	Complex(double x) { real = x; image = 0; }

	void SetReal(double value) { real = value; }
	void SetImage(double value) { image = value; }

	void print() {
		if (image == 0) { cout << "\n" << real << "\n"; return; }
		if (real == 0) { cout << "\n" << image << "i\n"; return; }
		if (image > 0) { cout << "\n" << real << " + " << image << "i\n"; }
		else { cout << "\n" << real << " - " << -image << "i\n"; }
	}
	double getReal() { return real; }
	double getImage() { return image; }
	double Module() { return sqrt(real * real + image * image); }
	double pr() { return real; }

	Complex operator*(double z) { Complex res(real * z, image * z); return res; }
	Complex operator+() { Complex res(real, -image); return res; }
	int operator<(Complex b) {
		if (real < b.real || real > b.real) { return real < b.real; }
		else { return image < b.image; }
	}
	int operator<(double b) { Complex F(b); Complex tmp(real, image); return tmp < F; }
	friend int operator<(double a, Complex b) { Complex F(a); return F < b; }
};