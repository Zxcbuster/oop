#include <iostream>
using namespace std;
class MyArrayParent
{
protected:
	int capacity;
	int count;
	double* ptr;
public:
	// конструкторы и деконструктор
	MyArrayParent(int Dimension = 100) { ptr = new double[Dimension]; capacity = Dimension; count = 0; }
	MyArrayParent(double* arr, int len) {
		ptr = new double[len];
		if (ptr != NULL) { capacity = count = len; for (int i = 0; i < len; i++) { ptr[i] = arr[i]; } }
		else { cout << "памяти нет:("; }
	}
	MyArrayParent(const MyArrayParent& v) {
		ptr = new double[capacity];
		if (ptr != NULL) { capacity = v.capacity; count = v.count; for (int i = 0; i < count; i++) { ptr[i] = v.ptr[i]; } }
		else { cout << "памяти нет:("; }
	}
	~MyArrayParent() { delete[] ptr; }

	// доступ к значениям полей
	int Capacity() { return capacity; }
	int Size() { return count; }

	//методы
	double GetComponent(int index) { if (index >= 0 && index < count) { return ptr[index]; } return -1; }
	virtual int IndexOf(double d) { for (int i = 0; i < count; i++) { if (ptr[i] == d) { return 1; } } return 0; }
	virtual void print() {
		cout << "\nMyArrParent, size: " << count << ", values: {";
		int i = 0; for (i = 0; i < count; i++) { cout << ptr[i]; if (i != count - 1) { cout << ", "; } } cout << "}\n";
	}
	virtual void push(double value) { if (count < capacity) { ptr[count] = value; count++; } }
	void SetComponent(int index, double value) { if (index >= 0 && index < count) { ptr[index] = value; } }
	void RemoveLastValue() { if (count >= 0) { count--; } }

	//перегрузки операций
	double& operator[](int index) {
		if (index >= 0 && index < count) { double a = GetComponent(index); return a; }
	}
	MyArrayParent& operator=(const MyArrayParent& v) {
		if (this == &v) { return *this; } //обратоботка случая A = A

		ptr = new double[capacity];
		if (ptr != NULL) { capacity = v.capacity; count = v.count; for (int i = 0; i < count; i++) { ptr[i] = v.ptr[i]; } }
		else { cout << "памяти нет:("; }
		return *this;
	}
};
class MyArrayChild : public MyArrayParent
{
public:
	//методы
	virtual void print() {
		cout << "\nMyArrChild, size: " << count << ", values: {";
		for (int i = 0; i < count; i++) { cout << ptr[i]; if (i != count - 1) { cout << ", "; } } cout << "}\n";
	}
	void InsertAt(double value, int index = -1) {
		if (index == -1) { MyArrayParent::push(value); return; }
		if (index >= 0 && index < count) {
			double* t = new double[count + 1]; int k = 0;
			for (int i = 0; i < count; i++) { if (i == index) { t[k] = value, k++; } t[k] = ptr[i], k++; }
			count++; ptr = t;
		}
	}
	void RemoveAt(int index = -1) {
		if (index == -1) { RemoveLastValue(); return; }
		if (index >= 0 && index < count) {
			for (; index < count - 1; index++) { ptr[index] = ptr[index + 1]; } count--;
		}
	}
	MyArrayChild task() {
		MyArrayChild T;
		for (int i = 0; i < count; i++) {
			int f = ptr[i], a = f / 1000, b = (f / 100) % 10, c = (f % 100) / 10, d = f % 10;
			if ((a + c) % 3 == 0 && (b + d) % 7 == 0) { T.push(f); }
		}
		return T;
	}
};
class MySortedArray : public MyArrayChild
{
public:
	//методы
	void print() {
		cout << "\nMySortedArray, size: " << count << ", values: {";
		int i = 0; for (i = 0; i < count; i++) { cout << ptr[i]; if (i != count - 1) { cout << ", "; } } cout << "}\n";
	}
	void push(double value) {
		if (count == 0) { MyArrayParent::push(value); return; }
		int l = 0, r = count - 1, m = (l + r) / 2;
		while (ptr[m] != value && l <= r) { m = (r + l) / 2; (ptr[m] < value) ? l = m + 1 : r = m - 1; }
		if (m > 0 && m < count - 1) {
			if (ptr[m] >= value) { InsertAt(value, m); }
			else { InsertAt(value, m + 1); }
		}
		else if (m == 0 && ptr[m] >= value) { InsertAt(value, m); }
		else if (m == count - 1 && ptr[m] <= value) { MyArrayParent::push(value); }
	}
	int IndexOf(double d) {
		int l = 0, r = count - 1, m = (l + r) >> 1;
		while (ptr[m] != d && l <= r) { m = (r + l) / 2; (ptr[m] < d) ? l = m + 1 : r = m - 1; }
		if (ptr[m] == d) { return 1; }
		return 0;
	}
	MySortedArray task() {
		if (count == 0) { return *this; } //случай когда объект пустой

		MySortedArray T;
		for (int i = 0; i < count; i++) {
			int f = ptr[i], a = f / 1000, b = (f / 100) % 10, c = (f % 100) / 10, d = f % 10;
			if ((a + c) % 3 == 0 && (b + d) % 7 == 0) { T.push(f); }
		}
		return T;
	}

};