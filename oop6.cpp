#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <random>
#include <cmath>
#include <complex>
using namespace std;

class Exception : public std::exception
{
protected:
	char* str;
public:
	//конструкторы и деструктор
	Exception(const char* s) {
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& e) {
		str = new char[strlen(e.str) + 1];
		strcpy_s(str, strlen(e.str) + 1, e.str);
	}
	~Exception() { if (str != "\0") { delete[] str; } }

	//метод
	virtual void print() { cout << "Exception: " << str; }
};
class Memorry_Error : public Exception
{
public:
	Memorry_Error() : Exception("Not enought memory") {}
	void print() { cout << "Not enought memory\n"; }
};
class OneIndexOutOfBounds : public Exception
{
protected:
	int i;
public:
	OneIndexOutOfBounds(int a) : Exception("Index out of bounds") { i = a; }
	void print() { cout << "Index " << i << " out of bounds of array\n"; }
};

template<class T> class Element
{
public:
	Element* next;
	Element* prev;
	T info;
	Element(T data, Element<T>* Next = NULL, Element<T>* Prev = NULL) { next = Next; prev = Prev; info = data; }
	Element(const Element& el) { next = el.next; prev = el.prev; info = el.info; }
	template<class T> friend ostream& operator<<(ostream& s, Element<T>& el);
	~Element() { if (next != NULL) { delete next; }; if (prev != NULL) { delete prev; } }
};
template<class T>  ostream& operator<<(ostream& s, Element<T>& el) { 
	s << el.info; return s;
}
template<class T> class LinkedList
{
protected:
	Element<T>* head;
	Element<T>* tail;
	int count;
public:

	LinkedList() { head = tail = NULL; count = 0; }
	Element<T>& operator[] (int index) {
		Element<T>* current = head;			
		for (int i = 0; current != NULL && i < index; current = current->next, i++);
		return *current;
	}
	virtual Element<T>* pop() = 0;
	virtual Element<T>* push(T value) = 0;
	virtual bool isEmpty() { return (LinkedList<T>::count == 0); }
	template<class T1> friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
	virtual ~LinkedList() { head = tail = NULL; }
};
template<class T> ostream& operator<<(ostream& s, LinkedList<T>& el) {
	Element<T>* current;
	for (current = el.head; current != NULL; current = current->next) { s << *current << "; "; }
	return s;
}
template<class T> class Queue : public LinkedList<T>
{
public:
	Queue() : LinkedList<T>() {}
	Queue(T* arr, int len) : LinkedList<T>(arr, len) {
		LinkedList<T>::count = 0;
		if (len > 0) {
			if (Element<T>* curr = new Element<T>(&arr[0])) {
				LinkedList<T>::head = curr; LinkedList<T>::count++;
				for (int i = 1; i < len; i++) {
					if (curr->next = new Element<T>(&arr[i], curr)) {
						curr = curr->next;
						LinkedList<T>::count++;
					}
					else { throw Memorry_Error(); }
				}
			}
			else { throw Memorry_Error(); }
		}
		else { LinkedList<T>::head = LinkedList<T>::tail = NULL; }
	}
	virtual Element<T>* push_end(T value) {
		if (LinkedList<T>::head == NULL) {
			if (LinkedList<T>::head = new Element<T>(value)) {
				LinkedList<T>::tail = LinkedList<T>::head;
			}
			else { throw Memorry_Error(); }
		}
		else {
			if (LinkedList<T>::tail->next = new Element<T>(value)) {
				LinkedList<T>::tail->next->prev = LinkedList<T>::tail;
				LinkedList<T>::tail = LinkedList<T>::tail->next;
			}
			else { throw Memorry_Error(); }
		}
		LinkedList<T>::count++;
		return LinkedList<T>::tail;
	}
	virtual Element<T>* push(T value) {
		if (LinkedList<T>::head == NULL) {
			if (LinkedList<T>::head = new Element<T>(value)) {
				LinkedList<T>::tail = LinkedList<T>::head;
			}
			else { throw Memorry_Error(); }
		}
		else {
			if (LinkedList<T>::head->prev = new Element<T>(value)) {
				LinkedList<T>::head->prev->next = LinkedList<T>::head;
				LinkedList<T>::head = LinkedList<T>::head->prev;
			}
			else { throw Memorry_Error(); }
		}
		LinkedList<T>::count++;
		return LinkedList<T>::head;
	}
	virtual Element<T>* pop()
	{
		if (LinkedList<T>::head == NULL) { return NULL; }
		Element<T>* res = LinkedList<T>::tail;
		if (LinkedList<T>::head == LinkedList<T>::tail) { LinkedList<T>::head = LinkedList<T>::tail = NULL; }
		else { LinkedList<T>::tail = LinkedList<T>::tail->prev; }
		LinkedList<T>::count--;
		return res;
	}
	virtual Element<T>* pop_start()
	{
		if (LinkedList<T>::head == NULL) { return NULL; }
		Element<T>* res = LinkedList<T>::head;
		if (LinkedList<T>::head == LinkedList<T>::tail) { LinkedList<T>::head = LinkedList<T>::tail = NULL; }
		else { LinkedList<T>::head = LinkedList<T>::head->next; }
		LinkedList<T>::count--;
		return res;
	}
	virtual Element<T>* insert(int index, T value) {
		if (index < 0 || index > LinkedList<T>::count) { throw OneIndexOutOfBounds(index); }
		if (index == 0) { return push(value); }
		if (index == LinkedList<T>::count) { return push_end(value); }
		Element<T>* current = LinkedList<T>::head;
		for (int i = 0; current != NULL && i < index - 1; current = current->next, i++);
		Element<T>* tmp = current->next; 
		if (current->next = new Element<T>(value)) {
			current->next->prev = current; current->next->next = tmp; tmp->prev = current->next;
			LinkedList<T>::count++;
			return current->next;
		}
		else { throw Memorry_Error(); }
	}
	virtual Element<T>* remove(int index) {
		if (index < 0 || index > LinkedList<T>::count) { throw OneIndexOutOfBounds(index); }
		if (index == 0) { return pop_start(); }
		if (index == LinkedList<T>::count) { return pop(); }
		Element<T>* current = LinkedList<T>::head;
		for (int i = 0; current != NULL && i < index - 1; current = current->next, i++);
		Element<T>* tmp = current->next->next; current->next = NULL; current->next = tmp; tmp->prev = current;
		LinkedList<T>::count--;
		return current->next;
	}
	virtual Element<T>* find(T filter) {
		for (Element<T>* ptr = LinkedList<T>::head; ptr != nullptr; ptr = ptr->next) {
			if (ptr->info == filter) { return ptr; }
		}
		return nullptr;
	}
	virtual LinkedList<T>* find_filter(bool (*f)(const T&, const T&), const T& data) {
		if (LinkedList<T>* l = new Queue<T>()) {
			for (Element<T>* ptr = LinkedList<T>::head; ptr != nullptr; ptr = ptr->next) {
				if (f(ptr->info, data)) { l->push(ptr->info); }
			}
			return l;
		}
		else { throw Memorry_Error(); }
	}
	virtual bool save(const char* root) {
		std::ofstream f(root); 
		if (f) { 
		for (Element<T>* ptr = LinkedList<T>::head; ptr != NULL; ptr = ptr->next) { f << "\n" << ptr->info; }
		f.close(); return true; 
		}
		else { return false; }
	}
	virtual bool load(const char* smth) {
		std::ifstream f(smth);
		if (f) {
		while (!f.eof()) { T a; f >> a; this->push(a); }
		f.close(); return true;
		}
		else { return false; }
	}
	~Queue() {
		if (LinkedList<T>::head != NULL) {
			while (LinkedList<T>::head->next != NULL) {
				LinkedList<T>::head = LinkedList<T>::head->next; LinkedList<T>::head->prev = NULL;
			}
			LinkedList<T>::head = NULL;
		}

	}
};

class Complex
{
public:
	double real; double image;
	Complex() { real = image = 0; }
	Complex(double r, double im) { real = r; image = im; }
	Complex(double x) { real = x; image = 0; }
	Complex(const Complex& el) { real = el.real; image = el.image; }

	double module() { return std::sqrt(real * real + image * image); }
	double pr() { return real; }
	Complex s() { Complex res(real, -image); return res; }
	Complex sqrt(Complex a) {
		complex<double> temp = (a.real, a.image); double f = arg(temp), r = pow(a.module(), 0.5);
		Complex res(r * cos(f / 2), r * sin(f / 2)); return res;
	}
	Complex operator*(double z) { Complex res(real * z, image * z); return res; }
	Complex operator+(Complex z) { Complex res(real + z.real, image + z.image); return res; }
	Complex operator-(Complex z) { Complex res(real - z.real, image - z.image); return res; }
	Complex operator-() { Complex res(-real, -image); return res; }
	Complex operator*(Complex z) { Complex res(real * z.real - image * z.image, real * z.image + image * z.real); return res; }
	Complex operator/(Complex z) {
		Complex tmp(*this); tmp = tmp * z.s(); double k = z.real * z.real + z.image * z.image;
		Complex out(tmp.real / k, tmp.image / k); return out;
	}
	friend Complex operator*(double a, Complex b) { Complex F(a * b.real, a * b.image); return F; }
	friend ostream& operator<<(ostream& s, Complex& el) { cout << el.real << " + i*(" << el.image << "); "; return s; }
	bool operator==(const Complex& a) { return (this->real == a.real && this->image == a.image); }
};
class Complex_equation : public Complex
{
public:
	Complex a, b, c, x1, x2;
	Complex_equation(Complex a1 = 0, Complex b1 = 0, Complex c1 = 0) {
		a = a1; b = b1; c = c1;
		Complex D = b * b - 4 * a * c; x1 = (-b + sqrt(D)) / (2 * a); x2 = (-b - sqrt(D)) / (2 * a);
	}
	friend ostream& operator<<(ostream& s, Complex_equation& el) { cout << el.x1 << el.x2 << "\n"; return s; }
	friend istream& operator>>(istream& s, Complex_equation& el) {
		cin >> el.a.real >> el.a.image >> el.b.real >> el.b.image >> el.c.real >> el.c.image;
		return s;
	}
	bool operator==(const Complex_equation& a) { return (this->x1 == a.x1 && this->x2 == a.x2); }
};
void test_oop6() {
	cout << "Only object\n";
	Queue<int> Q;
	for (int i = 0; i < 100; i += 5) { Q.push(i); }
	//Q.insert(5, 214921); Q.remove(2); cout << Q.find(214921) << "\n";
	for (; !Q.isEmpty(); cout << Q.pop()->info << ", "); cout << "\n";


	cout << "\nBase pointer 1\n";
	LinkedList<int>* ptr = new Queue<int>;
	for (int i = 1; i < 100; i += 5) { ptr->push(i); }
	cout << *ptr << "\n"; delete ptr;

	if (true) {
		cout << "\nBase pointer 2\n";
		LinkedList<int>* ptr; Queue<int>* ptr2 = new Queue<int>; ptr = ptr2;
		for (int i = 1; i < 100; i += 5) { ptr->push(i); }
		cout << *ptr << "\n"; delete ptr;
	}
	if (true) {
		cout << "\nQueue pointer\n";
		Queue<int>* ptr = new Queue<int>;
		for (int i = 2; i < 100; i += 5) { ptr->push(i); }
		cout << *ptr << "\n"; delete ptr;
	}
	if (true) {
		Queue<Complex_equation> R;
		for (int i = 8; i < 10; i++) {
			for (int j = 5; i < 10; i++) {
				Complex a(i, j), b(i, j - 2), c(i * j, i + 1);
				R.push(Complex_equation(a, b, c));
			}
		}
		cout << R;
		cout << typeid(R[1]).name();
	}
}