#include <iostream>
using namespace std;
class BaseString
{
protected:
	char* p; int len; int capacity;
public:
	//конструкторы и деструктор
	BaseString(char const* ptr)
	{
		if (ptr != nullptr) {
			cout << "\nBase Constructor 1\n";
			len = strlen(ptr) + 1;
			capacity = 256;
			if (p = new char[capacity]) {
				for (int i = 0; i < len; i++) { p[i] = ptr[i]; }
				p[len] = '\0';
			}
		}
	}
	BaseString(int Capacity = 256)
	{
		cout << "\nBase Constructor 0\n";
		if ((capacity = Capacity) > 0) {
			p = new char[capacity];
		}
		len = 0;
	}
	BaseString(const BaseString& s) {
		cout << "\nBase Copy Constructor\n";
		len = s.len;
		capacity = s.capacity;
		if (p = new char[capacity]) {
			for (int i = 0; i < s.len - 1; i++) { p[i] = s.p[i]; }
		}
	}
	~BaseString()
	{
		cout << "\nBase Destructor\n";
		if (p != NULL)
			delete[] p;
	}


	//методы
	int Length() { return len; }
	int Capacity() { return capacity; }
	char& operator[](int i) const { return p[i]; }
	BaseString& operator=(const BaseString& s)
	{
		if (this == &s) { return *this; } //обратоботка случая A = A
		cout << "\nBase Operator = \n";
		len = s.len;
		capacity = s.capacity;
		if (p = new char[capacity]) {
			for (int i = 0; i < s.len; ++i) { p[i] = s.p[i]; }
			p[len - 1] = '\0';
			return *this;
		}
	}
	virtual void print()
	{
		int i = 0;
		while (p[i] != '\0') { cout << p[i]; i++; }
	}
};
class ChildString : public BaseString
{
	ChildString(const ChildString& s) {
		cout << "\nChild Copy Constructor\n";
		len = s.len;
		capacity = s.capacity;
		if (p = new char[capacity]) {
			for (int i = 0; i < s.len - 1; i++) { p[i] = s.p[i]; }
		}
	}
	ChildString(int Capacity = 256) {}
	ChildString& operator=(const ChildString& s)
	{
		if (this == &s) { return *this; } //обратоботка случая A = A
		cout << "\nChild Operator = \n";
		len = s.len;
		p = new char[s.capacity];
		capacity = s.capacity;
		if (p = new char[capacity]) {
			for (int i = 0; i < s.len; i++) { p[i] = s.p[i]; }
			p[len - 1] = '\0';
			return *this;
		}
	}
	ChildString task() {
		if (len = 0) { return *this; } //случай когда объект пустой
		ChildString T; int i = 0;
		while (p[i] != '\0') {
			T[i] = (p[i] >= '0' && p[i] <= '9') ? p[i] : T[i]; i++;
		}
		return T;
	}
};