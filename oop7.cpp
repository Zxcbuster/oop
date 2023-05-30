#include <iostream>
#include <fstream>
#include <random>
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

template<class T>
void copy(T from[], T to[], long size) {
	int i; for (i = 0; i < size; i++) { to[i] = from[i]; }
}
int random(int low, int high)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}
template<class T> T* count_sort(T* a, size_t len) {
	T max = a[0]; for (int i = 0; i < len; i++) { (a[i] > max) ? max = a[i] : max; }
	T min = a[0]; for (int i = 0; i < len; i++) { (a[i] < min) ? min = a[i] : min; }
	int k = max - min + 1; T* count = new T[k]; T* output = new T[len];
	if (output != nullptr && count != nullptr) {
		for (int i = 0; i < k; i++) { count[i] = 0; }
		for (int i = 0; i < len; i++) { count[a[i] - min]++; } int k = 0;
		for (int j = min; j <= max; j++) { for (int i = 0; i < count[j - min]; i++) { output[k++] = j; } }
		return output;
	}
	else { throw Memorry_Error(); }

}
void counting_sort_for_radix(int* array, int size, int place) {
	const int max = 10; int* output = new int[size]; int* count = new int[max];
	if (output != nullptr && count != nullptr) {
		for (int i = 0; i < max; ++i) { count[i] = 0; }
		for (int i = 0; i < size; i++) { count[(array[i] / place) % 10]++; }
		for (int i = 1; i < max; i++) { count[i] += count[i - 1]; }
		for (int i = size - 1; i >= 0; i--) {
			output[count[(array[i] / place) % 10] - 1] = array[i];
			count[(array[i] / place) % 10]--;
		}
		for (int i = 0; i < size; i++) { array[i] = output[i]; }
	}
	else { throw Memorry_Error(); }
}
template<class T> T* radix_sort(T* arr, size_t size) {
	if (T* a = new T[size]) {
		::copy(arr, a, size);
		T max = a[0]; for (int i = 0; i < size; i++) { (a[i] > max) ? max = a[i] : max; }
		for (int place = 1; max / place > 0; place *= 10) { ::counting_sort_for_radix(a, size, place); }
		return a;
	}
	else { throw Memorry_Error(); }
}

void test_oop7() {
	const int N = 1000;  int arr1[N];
	for (int i = 0; i < N; i++) { arr1[i] = random(-N, N); }
	std::ofstream fout("c:\\users\\kurop\\onedrive\\рабочий стол\\arr1.txt");
	if (fout) { fout << N << "\n"; for (int i = 0; i < N; i++) { fout << arr1[i] << " "; }; fout.close(); }
	ifstream fin("c:\\users\\kurop\\onedrive\\рабочий стол\\arr1.txt");
	int* random; int len = 0;
	if (fin) {
		fin >> len;
		random = new int[len];
		for (int i = 0; i < len; i++) { fin >> random[i]; }
		time_t time1, time2;
		time1 = clock();
		int* res1 = count_sort(arr1, N);
		time2 = clock();
		cout << ((double)(time2)-time1) / CLOCKS_PER_SEC;
		ofstream fres1("c:\\users\\kurop\\onedrive\\рабочий стол\\res1.txt");
		if (fres1)
		{
			fres1 << N << "\n";
			for (int i = 0; i < N; i++)
				fres1 << res1[i] << " ";
			fres1.close();
		}
		delete[] res1;
		delete[] random;
		fin.close();
	}
}