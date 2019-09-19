#include <iostream>
#include <thread>

using namespace std;

void F1(char c, int n)
{
	for (int i = 0; i < n; i++)
		cout << c;
}


int calculadora(int x, int y)
{
	return x + y;
}
void main()
{
	int temp;
	int nt = thread::hardware_concurrency();
	thread t=thread(F1,'c',10);
	temp=calculadora(10, 5);
	cout << temp;
	t.join();
}

---------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <vector>

#include<stdlib.h>
using namespace std;

void merge(vector<long>& vec, int start, int mid, int end)
{
	vector<int> one(vec.begin() + start, vec.begin() + mid + 1);
	vector<int> two(vec.begin() + mid + 1, vec.begin() + end + 1);

	int a = 0;
	int b = 0;
	int index = start;
	while (a < one.size() && b < two.size())
	{
		if (one[a] < two[b])
			vec[index++] = one[a++];
		else
			vec[index++] = two[b++];
	}

	while (a < one.size())
		vec[index++] = one[a++];
	while (b < two.size())
		vec[index++] = two[b++];
}


void merge_sort(vector<long>& vec, int start, int end)
{
	if (start >= end)
		return;
	

	int mid = start + (end - start) / 2;
	thread first(merge_sort, std::ref(vec), start, mid);
	thread second(merge_sort, std::ref(vec), mid + 1, end);
	first.join();
	second.join();
	merge(vec, start, mid, end);
}

void procesador(int a, int& nt)
{
	if (a == 0)
		return;
	while ((a < nt))
		nt /= 2;

}

void cut(vector<long>& vec, int start, int end, int nt)
{
	merge_sort(vec, 0, end);
}

void rellenar(int tam, int* ptr)
{
	srand(time(NULL));
	for (int c = 0; c < tam; c++)
	{
		int num = 1 + rand() % (11 - 1);
		*(ptr + c) = num;
	}
	cout << "La matriz generada:";
	for (int i = 0; i < tam; i++)
	{

		cout << ptr[i] << " ";
	}
	cout << "\n\n\n";
}
int main()
{
	int nt = thread::hardware_concurrency();
	int tam;
	cout << "ingrese el tamaño de su array: ";
	cin >> tam;
	int* a = new int[tam];
	rellenar(tam, a);
	int size = tam;
	vector<long> vec(a, a + size + 1);
	procesador(size, nt);
	int size2 = size / nt;
	
	while (size2 <= size)
	{
		cut(vec, 0, size2, nt);
		size2 += size2;
	}
	for (int i = 0; i < size-1; i++)
	
		cout << vec[i]<<" ";
	
}
-------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include<stdlib.h>

using namespace std;

void merge(vector<long>& vec, long start, long mid, long end)
{
	vector<int> one(vec.begin() + start, vec.begin() + mid + 1);
	vector<int> two(vec.begin() + mid + 1, vec.begin() + end + 1);

	int a = 0;
	int b = 0;
	int index = start;
	while (a < one.size() && b < two.size())
		(one[a] < two[b])? vec[index++] = one[a++]: vec[index++] = two[b++];

	while (a < one.size())
		vec[index++] = one[a++];
	while (b < two.size())
		vec[index++] = two[b++];
}

void merge_sort(vector<long>& vec, long start, long end)
{
	if (start >= end)
		return;
	thread t[2];
	int mid = start + (end - start) / 2;
	for (int i = 0; i < 1; i++)
	{
		t[i] = thread(merge_sort, std::ref(vec), start, mid);
		t[i + 1] = thread(merge_sort, std::ref(vec), mid + 1, end);
	}
	for (int i = 0; i < 2; i++)
		t[i].join();
	merge(vec, start, mid, end);
}


void procesador(int a, int& nt)
{
	if (a == 0)
		return;
	while ((a < nt))
		nt /= 2;
}


void rellenar(int tam, int* ptr)
{
	srand(time(NULL));
	for (int c = 0; c < tam; c++)
	{
		int num = 1 + rand() % (11 - 1);
		*(ptr + c) = num;
	}
	cout << "La matriz generada:";
	for (int i = 0; i < tam; i++)
	{

		cout << ptr[i] << " ";
	}
	cout << "\n\n\n";
}
int valides(vector<long>& vec, long size)
{
	if (size <= 7 && size > 1)
	{
		merge_sort(vec, 0, size);
		return 0;
	}
	else return 0;
}
int main()
{
	int nt = thread::hardware_concurrency();
	int tam, tam2 = 0, size3, size2;
	int temp = 0, temp2,validez=0;

	cout << "ingrese el tamaño de su array: ";
	cin >> tam;

	int size = tam;
	int* a = new int[tam];
	size2 = size / nt;

	rellenar(tam, a);

	vector<long> vec(a, a + size + 1);

	procesador(size, nt);
	while (size2 > 1500)
		size2 = size2 / nt;
	//cout << size2;
	size3 = size2;
	temp2 = size3;
	validez=valides(vec, size);
	while (temp <= nt && validez!=0)
	{
		while (size2 <= size)
		{
			merge_sort(vec, tam2, size2);
			tam2 = size2;
			size2 += size3;

		}

		temp++;
		tam2 = 0;
		size3 = size2;
		size2 = temp2 * temp;
		//cout << size2 << " ";
		if (size2 >= 1499)
		{
			temp = 0;
			break;
		}

		//size2 = size3;
	}
	if (temp == 0 && validez!=0)
		std::sort(vec.begin(), vec.begin() + size + 1);
	else {
		merge_sort(vec, 0, size);
	}
	for (int i = 1; i <=size ; i++)
		cout << vec[i] << " ";
}
