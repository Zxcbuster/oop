#include <iostream>
using namespace std;
class A1
{
protected:
	int a1;
public:
	A1(int V1 = 0) { a1 = V1; cout << "\nClass A1 constructor"; }
	virtual void print() { cout << "\nVariable of A1 class"; }
	virtual void show() { cout << "\na1 = " << a1; }
};
class B1 : virtual public A1
{
protected:
	int b1;
public:
	B1(int V1 = 0, int V2 = 0) : A1(V2) { b1 = V1; cout << "\nClass B1 constructor"; }
	virtual void print() { cout << "\nVariable of B1 class"; }
	virtual void show() { cout << "\nb1 = " << b1 << ", a1 =" << a1; }
};
class B2 : virtual public A1
{
protected:
	int b2;
public:
	B2(int V1 = 0, int V2 = 0) : A1(V2) { b2 = V1; cout << "\nClass B2 constructor"; }
	virtual void print() { cout << "\nVariable of B2 class"; }
	virtual void show() { cout << "\nb2 = " << b2 << ", a1 = " << a1; }
};
class B3 : virtual public A1
{
protected:
	int b3;
public:
	B3(int V1 = 0, int V2 = 0) : A1(V2) { b3 = V1; cout << "\nClass B3 constructor"; }
	virtual void print() { cout << "\nVariable of B3 class"; }
	virtual void show() { cout << "\nb3 = " << b3 << ", a1 =" << a1; }
};
class B4 : virtual public A1
{
protected:
	int b4;
public:
	B4(int V1 = 0, int V2 = 0) : A1(V2) { b4 = V1; cout << "\nClass B4 constructor"; }
	virtual void print() { cout << "\nVariable of B4 class"; }
	virtual void show() { cout << "\nb4 = " << b4 << ", a1 =" << a1; }
};
class C1 :virtual public B1, virtual public B2, virtual public B3, virtual public B4
{
protected:
	int c1;
public:
	C1(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0, int V6 = 0) : A1(V6), B1(V5), B2(V4), B3(V3), B4(V2) {
		c1 = V1; cout << "\nClass C1 constructor";
	}
	virtual void print() { cout << "\nVariable of C1 class"; }
	virtual void show() { cout << "\nc1 = " << c1 << ", b1 =" << b1 << ", b2 =" << b2 << ", b3 =" << b3 << ", b4 =" << b4 << ", a1 =" << a1; }
};
class C2 :virtual public B1, virtual public B2, virtual public B3, virtual public B4
{
protected:
	int c2;
public:
	C2(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0, int V6 = 0) : A1(V6), B1(V5), B2(V4), B3(V3), B4(V2) {
		c2 = V1; cout << "\nClass C2 constructor";
	}
	virtual void print() { cout << "\nVariable of C2 class"; }
	virtual void show() { cout << "\nc2 = " << c2 << ", b1 =" << b1 << ", b2 =" << b2 << ", b3 =" << b3 << ", b4 =" << b4 << ", a1 =" << a1; }
};