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
		return 1;
	}
	if (size < 2 && size >= 0)
		return -1;
	return 0;
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
	while (size2 >= 1499)
		size2 = size2 / nt;
	//cout << size2;
	size3 = size2;
	temp2 = size3;
	validez=valides(vec, size);
	while (temp <= nt && validez!=1 && validez!=-1)
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
	if (temp == 0 && validez!=1 )
		std::sort(vec.begin(), vec.begin() + size + 1);
	if  (validez==1)
		merge_sort(vec, 0, size);
	if (temp!=0 && validez!=1)
		merge_sort(vec, 0, size);
	for (int i = 1; i <=size ; i++)
		cout << vec[i] << " ";
}
----------------------------------------------
	
#include<stdlib.h> 
#include<stdio.h> 
#include <iostream>
#include <time.h>
#include <thread>

using namespace std;


class valores {
public:
	int a, b;
	void set_val(long& x, long& y)
	{
		a = x; b = y;
	}
};
class menor :public valores {
public:
	bool ordenar()
	{
		if (a < b)
		{
			return 1;
		}
	}
};
class mayor :public valores {
public:
	bool ordenar()
	{
		if (a > b)
			return 1;
	}
};



struct Greater
{
	bool cmp(long& a, long& b) {
		//cout <<'\n'<< a << " " <<b<<endl;
		if (a > b)
			return 1;
	}
};
// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(long* arr, long l, long m, long r)
{
	long i, j, k;
	long n1 = m - l + 1;
	long n2 = r - m;

	/* create temp arrays */
	long* L = new long[n1];
	long* R = new long[n2];
	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete L;
	delete R;
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(long* arr, long l, long r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		long m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}


/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(long A[], long size)
{
	long i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}



struct Less
{
	inline int cmp(long* ptr, long size) {
		return 1;
	}
};
void copiar(long* ptr, long* ptr2, long* ptr3, long* ptr4, long tam)
{
	for (long i = 0; i < tam; i++)
	{
		*(ptr2 + i) = *(ptr + i);
		*(ptr3 + i) = *(ptr + i);
		*(ptr4 + i) = *(ptr + i);
	}
}
void rellenar(long tam, long* ptr)
{
	srand(time(NULL));
	for (long c = 0; c < tam; c++)
	{
		long num = 1 + rand() % (11 - 1);
		*(ptr + c) = num;
	}
	cout << "La matriz generada:";
	//for (int i = 0; i < tam; i++)
//	cout << ptr[i] << " ";
	
	//cout << endl;
}

void ptr_function(long* tam, long arr_size, void (*f)(long*, long, long))
{
	clock_t t1, t2;
	float diff;
	t1 = clock();
	(*f)(tam, 0, arr_size - 1);
	t2 = clock();
	printf("\nSorted array bt funcion \n");
	//printArray(tam, arr_size);
	diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	cout << "Running time: " << diff << endl;
	

}

void poli(long* ptr3, long size) { //poli
	menor m;
	valores* v = &m;
	clock_t t1, t2;
	float diff;
	t1 = clock();
	
	bool b;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			v->set_val(*(ptr3 + i), *(ptr3 + j));
			b = m.ordenar();
			if (b == 1)
			{
				swap(*(ptr3 + i), *(ptr3 + j));
				b = 0;

			}

		}
	}
	t2 = clock();
	printf("\nSorted array by poli \n");
	printArray(ptr3, size);
	diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	cout << "Running time: " << diff << endl;
}
template<typename T>
void ptr_class(long* ptr2, long size)
{ //punteor a clase
	T a;
	int b;
	clock_t t1, t2;
	float diff;
	t1 = clock();
	 b = a.cmp(ptr2, size);
	
	if (b == 1)
		mergeSort(ptr2, 0, size - 1);
	t2 = clock();
	printf("\nSorted array by functor \n");
	//printArray(ptr2, size);
	diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
	cout << "Running time: " << diff << endl;
}
/* Driver program to test above functions */
int main()
{
	thread t[3];
	long arr_size;
	cout << "ingrese el tamaño de su array: ";
	cin >> arr_size;
	long* tam = new long[arr_size];
	long* ptr2 = new long[arr_size];
	long* ptr3 = new long[arr_size];
	long* ptr4 = new long[arr_size];
	rellenar(arr_size, tam);
	copiar(tam, ptr2, ptr3, ptr4, arr_size);
	
	t[1]=thread(ptr_function,tam, arr_size, mergeSort);
	
	//poli(ptr3, arr_size);
	ptr_class<Less>(ptr2, arr_size);
	
	t[1].join();
	//t[3].join();
	delete tam;
	delete ptr2;
	//mergeSort(tam, 0, arr_size - 1);


	return 0;
}
