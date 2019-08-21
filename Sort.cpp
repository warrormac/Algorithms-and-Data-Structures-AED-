#include <iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

template <typename T>
struct Less
{
	int cmp(T* a, T* b) {
		return *a > * b;
	}
};

struct Greater
{
	void cmp(int &a, int &b) {
		cout <<'\n'<< a << " " <<b<<endl;
		if (a<b)
		{
			int h = a;
			a = b;
			b = h;
		}
		
	}
};


void rellenar(int tam, int* ptr)
{
	srand(time(NULL));
	for (int c = 0; c < tam; c++)
	{
		int num = 1 + rand() % (11 - 1);
		*(ptr + c) = num;
	}
	for (int i = 0; i < tam; i++)
	{
		cout << ptr[i]<<" ";
	}
}


void copiar(int* ptr, int* ptr2, int* ptr3, int* ptr4, int tam)
{
	for (int i = 0; i < tam; i++)
	{
		*(ptr2 + i) = *(ptr + i);
		*(ptr3 + i) = *(ptr + i);
		*(ptr4 + i) = *(ptr + i);
	}
}

bool mayorAmenor(int i, int j) {
	return i > j;
}
bool menorAmayor(int i, int j) {
	return i < j;
}
void swap(int& x, int& y) {
	int h = x;
	x = y;
	y = h;
}

void ptr_to_function(int* ptr, int size, bool(*f)(int, int)) { //punteor a funcion
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*f)(*(ptr + i), *(ptr + j)))
				swap(*(ptr + i), *(ptr + j));
		}
	}
	for (int i = 0; i < size; i++)
		cout << *(ptr + i) << " ";
	cout << endl;
}

template <typename G>
void ptr_to_function1(int* ptr2, int size) { //punteor a clase
	G a;
	bool b;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j <size; j++) {
			a.cmp(*(ptr2 + i), *(ptr2 + j));
			
		}
	}
	for (int i = 0; i < size; i++)
		cout << *(ptr2 + i) << " ";
	cout << endl;
}

int main()
{
	int tam;
	cout << "ingrese el tamaño de su array: ";
	cin >> tam;
	int* ptr = new int[tam];
	int* ptr2 = new int[tam];
	int* ptr3 = new int[tam];
	int* ptr4 = new int[tam];
	Greater a;


	rellenar(tam, ptr);
	copiar(ptr, ptr2, ptr3, ptr4, tam);
	//ptr_to_function(ptr, tam, menorAmayor);
	ptr_to_function1 < Greater > (ptr2, tam);



}

////////////////////////////////////////////////////////////////////////




#include <iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

template <typename T>
struct Less
{
	int cmp(T* a, T* b) {
		return *a > * b;
	}
};

struct Greater
{
	int cmp(int *a, int *b) {
		cout << "hola";
		
		int h = *a;
		*a = *b;
		*b = h;
		return a < b;
	}
};


void rellenar(int tam, int* ptr)
{
	srand(time(NULL));
	for (int c = 0; c < tam; c++)
	{
		int num = 1 + rand() % (11 - 1);
		*(ptr + c) = num;
	}
}


void copiar(int* ptr, int* ptr2, int* ptr3, int* ptr4, int tam)
{
	for (int i = 0; i < tam; i++)
	{
		*(ptr2 + i) = *(ptr + i);
		*(ptr3 + i) = *(ptr + i);
		*(ptr4 + i) = *(ptr + i);
	}
}

bool mayorAmenor(int i, int j) {
	return i > j;
}
bool menorAmayor(int i, int j) {
	return i < j;
}
void swap(int& x, int& y) {
	int h = x;
	x = y;
	y = h;
}

void ptr_to_function(int* ptr, int size, bool(*f)(int, int)) { //punteor a funcion
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*f)(*(ptr + i), *(ptr + j)))
				swap(*(ptr + i), *(ptr + j));
		}
	}
	for (int i = 0; i < size; i++)
		cout << *(ptr + i) << " ";
	cout << endl;
}

template <typename G>
void ptr_to_function1(int* ptr2, int size, G a) { //punteor a clase
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a.cmp((ptr2+i),(ptr2+j));
			//swap(*(ptr2 + i), *(ptr2 + j));
		}
	}
	for (int i = 0; i < size; i++)
		cout << *(ptr2 + i) << " ";
	cout << endl;
}

int main()
{
	int tam;
	cout << "ingrese el tamaño de su array: ";
	cin >> tam;
	int* ptr = new int[tam];
	int* ptr2 = new int[tam];
	int* ptr3 = new int[tam];
	int* ptr4 = new int[tam];
	Greater a;


	rellenar(tam, ptr);
	copiar(ptr, ptr2, ptr3, ptr4, tam);
	//ptr_to_function(ptr, tam, menorAmayor);
	ptr_to_function1(ptr2, tam,a);



}

