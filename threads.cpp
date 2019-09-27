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
#include <time.h> 


using namespace std;




void merge(long l, long m, long r, long *arr)
{
	long i, j, k;
	long n1 = m - l + 1;
	long n2 = r - m;

	
	long* L = new long[n1];
	long* R = new long[n2];
	
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	
	i = 0; 
	j = 0; 
	k = l; 
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
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	delete L;
	delete R;
}
// merge sort function --------------------------------------------------------------------------------------------------------------------------------
/*void merge_sort(int low, int high,long *a)
{
	// calculating mid point of array 
	int mid = low + (high - low) / 2;
	if (low < high) {

		// calling first half 
		merge_sort(low, mid,a);

		// calling second half 
		merge_sort(mid + 1, high,a);

		// merging the two halves 
		merge(low, mid, high,a);
	}
}*/

// thread function for multi-threading 
void merge_sort(int low, int high,long *a)
{
	// which part out of 4 parts 
	//int midd = part++;

	// calculating low and high 
	 //low = midd * (20/ 4);
	 //high = (midd + 1) * (20 / 4) - 1;

	// evaluating mid point 
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid,a);
		merge_sort(mid + 1, high,a);
		merge(low, mid, high,a);
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

int main()
{
	long tam, nt = 8;
	int i = 0;
	thread t[8];
	cout << "ingrese el tamaño: ";
	cin >> tam;
	long* a = new long[tam];
	rellenar(tam, a);

	long temp = 0, temp2, validez = 0, tam2 = 0;
	long size2 = tam / nt;
	long size3 = size2;
	// t1 and t2 for calculating time for 
	// merge sort 
	clock_t t1, t2;

	t1 = clock();


	temp2 = size3;

	// creating 4 threads 
	for (int i = 0; i < 8; i++,tam2 = size2,size2 += size3)
		t[i]=thread(merge_sort, tam2, size2,a);

	// joining all 4 threads 
	for (int i = 0; i < 8; i++)
		t[i].join();
	

	// merging the final 4 parts 
	//merge(0, (tam / 2 - 1) / 2, tam / 2 - 1,a);
	//merge(tam / 2, tam / 2 + (tam - 1 - tam / 2) / 2, tam - 1,a);
	merge_sort(0, tam - 1, a);

	t2 = clock();

	// displaying sorted array 
	cout << "Sorted array: ";
	//for (int i = 0; i < tam; i++)
		//cout << a[i] << " ";

	// time taken by merge sort in seconds 
	cout << "Time taken: " << (t2 - t1) /
		(double)CLOCKS_PER_SEC << endl;

	return 0;
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
