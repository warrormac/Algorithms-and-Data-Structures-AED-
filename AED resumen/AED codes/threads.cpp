#include <iostream> 
#include <thread> 
#include <time.h> 


using namespace std;




void merge(long l, long m, long r, long* arr)
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
void merge_sort(int low, int high, long* a)
{
	// which part out of 4 parts 
	//int midd = part++;

	// calculating low and high 
	 //low = midd * (20/ 4);
	 //high = (midd + 1) * (20 / 4) - 1;

	// evaluating mid point 
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid, a);
		merge_sort(mid + 1, high, a);
		merge(low, mid, high, a);
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
	for (int i = 0; i < 8; i++, tam2 = size2, size2 += size3)
		t[i] = thread(merge_sort, tam2, size2, a);

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