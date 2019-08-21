#include <iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;


void rellenar(int tam,int *ptr)
{
	srand(time(NULL));
	for (int c = 0; c < tam; c++)
	{
		int num = 1 + rand() % (11 - 1);
		*(ptr + c) = num;
	}
}


void copiar(int *ptr,int* ptr2, int* ptr3, int* ptr4,int tam)
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

int main()
{
	int tam;
	cout << "ingrese el tamaño de su array: ";
	cin >> tam;
	int* ptr = new int[tam];
	int* ptr2 = new int[tam];
	int* ptr3 = new int[tam];
	int* ptr4 = new int[tam];
	rellenar(tam,ptr);
	copiar(ptr, ptr2, ptr3, ptr4, tam);
	ptr_to_function(ptr, tam, menorAmayor);

	
	
}
