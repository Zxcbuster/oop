#include <iostream>
#include <fstream>
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
	void print() {
		cout << "Not enought memory\n";
	}
};
class IndexOutOfBounds : public Exception
{
protected:
	int i, j;
public:
	IndexOutOfBounds(int a, int b) : Exception("Index out of bounds") { i = a, j = b; }
	void print() {
		cout << "Index " << i << " " << j << " out of bounds of array\n";
	}

};
class OneIndexOutOfBounds : public Exception
{
protected:
	int i;
public:
	OneIndexOutOfBounds(int a) : Exception("Index out of bounds") { i = a; }
	void print() {
		cout << "Index " << i << " out of bounds of array\n";
	}
};
class WrongDimensionsException : public Exception
{
protected:
	int a, b, c, d;
public:
	WrongDimensionsException(int a1, int b1, int c1, int d1) : Exception("wrong dimensions exception") {
		a = a1, b = b1, c = c1, d = d1;
	}
	virtual void print() {
		cout << "the dimensions of the object are not comparable\n";
		cout << "[" << a << "," << b << "] " << "!= " << "[" << c << "," << d << "]\n";
	}
};
//классы матриц
template<class N> class BaseMatrix
{
protected:
	N** ptr;
	int height;
	int width;
	void rebuild(int Height, int Width) {
		if (Height <= 0 || Width <= 0)
			throw IndexOutOfBounds(Height, Width);
		if (ptr != nullptr) {
			for (int i = 0; i < height; i++)
				if (ptr[i] != nullptr) { delete[] ptr[i]; }
			delete[] ptr;
			ptr = nullptr;
		}
		if (ptr = new N * [Height]) {
			for (int i = 0; i < Height; i++) {
				ptr[i] = new N[Width];
				if (ptr[i] == nullptr) { throw Memorry_Error(); }
			}
		}
		else { throw Memorry_Error(); }
		height = Height;
		width = Width;
	}
public:
	//конструкторы и деструктор
	BaseMatrix<N>(int Height = 10, int Width = 10)
	{
		if (Height <= 0 || Width <= 0) { throw IndexOutOfBounds(Height, Width); }

		ptr = new N * [Height];
		if (ptr != nullptr) {
			for (int i = 0; i < Height; i++) {
				ptr[i] = new N[Width];
				if (ptr[i] == nullptr) { throw Memorry_Error(); }
			}
		}
		else { throw Memorry_Error(); }
		height = Height;
		width = Width;
	}
	BaseMatrix<N>(const BaseMatrix<N>& M)
	{
		if (ptr = new N * [M.height]) {
			for (int i = 0; i < M.height; i++) {
				if (ptr[i] = new N[M.width]) {
					for (int j = 0; j < M.width; j++) { ptr[i][j] = M.ptr[i][j]; }
				}
				else { throw Memorry_Error(); }
			}
		}
		else { throw Memorry_Error(); }
		height = M.height;
		width = M.width;
	}
	~BaseMatrix<N>()
	{
		if (ptr != nullptr) {
			for (int i = 0; i < height; i++) { delete[] ptr[i]; }
			delete[] ptr;
			ptr = nullptr;
		}
	}

	//методы
	void print() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) { cout << ptr[i][j] << " "; }
			cout << "\n";
		}
		cout << "\n";
	}
	N* operator[](int i) {
		if (i < 0 || i >= height) { throw OneIndexOutOfBounds(i); }
		return ptr[i];
	}
	N& operator()(int row, int column) {
		if (row < 0 || column < 0 || row >= height || column >= width) { throw IndexOutOfBounds(row, column); }
		return ptr[row][column];
	}
	BaseMatrix& operator=(const BaseMatrix& s) {
		if (this == &s) { return *this; }
		if (ptr != nullptr) {
			for (int i = 0; i < height; i++) { delete[] ptr[i]; }
			delete[] ptr;
			ptr = nullptr;
		}
		if (ptr = new N * [s.height]) {
			for (int i = 0; i < s.height; i++) {
				if (ptr[i] = new N[s.width]) {
					for (int j = 0; j < s.width; j++) { ptr[i][j] = s.ptr[i][j]; }
				}
				else { throw Memorry_Error(); }
			}
		}
		else { throw Memorry_Error(); }
		height = s.height;
		width = s.width;
	}
	template<class N>
	friend ostream& operator << (ostream& ustream, BaseMatrix<N> obj);
	template<class N>
	friend istream& operator >> (istream& ustream, BaseMatrix<N>& obj);
};
template<class N> ostream& operator << (ostream& ustream, BaseMatrix<N> obj)
{
	ustream << obj.height << " " << obj.width << "\n";
	if (obj.ptr != nullptr) {
		for (int i = 0; i < obj.height; i++) {
			for (int j = 0; j < obj.width; j++) {
				if (obj.ptr[i] != nullptr) {
					ustream << obj.ptr[i][j] << " ";
				}
				else { throw Memorry_Error(); }
			}
			ustream << "\n";
		}
	}
	else { throw Memorry_Error(); }
	ustream << "\n";
	return ustream;
}
template<class N> istream& operator >> (istream& ustream, BaseMatrix<N>& obj)
{
	int height, width; ustream >> height >> width; obj.rebuild(height, width);
	if (obj.ptr != nullptr) {
		for (int i = 0; i < obj.height; i++) {
			for (int j = 0; j < obj.width; j++) {
				if (obj.ptr[i] != nullptr) {
					ustream >> obj.ptr[i][j];
				}
				else { throw Memorry_Error(); }
			}
		}
	}
	else { throw Memorry_Error(); }
	cout << "\n";
	return ustream;
}
template <class N> class ChildMatrix : public BaseMatrix<N>
{
public:
	ChildMatrix(int Height = 10, int Width = 10) : BaseMatrix<N>(Height, Width) {}
	ChildMatrix task() {
		ChildMatrix T(*this);
		if (T.ptr == nullptr) { throw Exception("Not enought memory"); }
		for (int i = 0; i < T.height; i++) { if (T.ptr[i] == nullptr) { throw Memorry_Error(); } }
		for (int i = 0; i < T.height && i < T.width; i++) {
			int t = i;
			while (T.ptr[i][i] == 0 && t < T.height) {
				if (T.ptr[t][i] != 0) {
					for (int j = 0; j < T.width; j++) {
						N temp = T.ptr[i][j];
						T.ptr[i][j] = T.ptr[t][j];
						T.ptr[t][j] = temp;
					}
				}
				t++;
			}
			if (T.ptr[i][i] != 0 && T.ptr[i][i] != 1) { N temp = T.ptr[i][i]; for (int j = i; j < T.width; j++) { T.ptr[i][j] /= temp; } };  t = 0;
			while (t < T.height) {
				if (t != i && T.ptr[t][i] != 0) {
					N d = T.ptr[t][i];
					for (int j = 0; j < T.width; j++) { T.ptr[t][j] -= T.ptr[i][j] * d; }
				}
				t++;
			}
		}
		return T;
	}
};
void test_oop5() {
	ChildMatrix<double> A; cin >> A;
	ChildMatrix<double> B = A.task(); cout << B;

	try { BaseMatrix<double> Wrong(-2, 0); }
	catch (Exception e) { cout << "\nException has been caught: "; e.print(); cout << "\n"; }

	BaseMatrix<double> M; cin >> M;
	ofstream fout("C:\\Users\\Kurop\\OneDrive\\Рабочий стол\\out.txt");
	if (fout.is_open()) { fout << M; fout.close(); }
	ifstream fin("C:\\Users\\Kurop\\OneDrive\\Рабочий стол\\out.txt");
	BaseMatrix<double> M1; if (fin) { fin >> M1; fin.close(); }
	cout << M1;
	char c; cin >> c;
}