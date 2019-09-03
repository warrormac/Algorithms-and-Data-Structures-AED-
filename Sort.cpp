#include <iostream>
#include <thread>
#include<stdlib.h>
#include<time.h>

using namespace std;

class valores {
public:
	int a, b;
	void set_val(int& x, int& y)
	{
		a = x; b = y;
	}
};
struct Less
{
	inline void cmp(int& a, int& b) {
		if (a < b)
			swap(a, b);
	}
};

struct Greater
{
	bool cmp(int& a, int& b) {
		//cout <<'\n'<< a << " " <<b<<endl;
		if (a > b)
			return 1;
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
	cout << endl;
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
inline void swap(int& x, int& y) {
	int h = x;
	x = y;
	y = h;
}
template<typename T>
void ptr_to_function1(int* ptr2, int size) { //punteor a clase
	T a;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a.cmp(*(ptr2 + i), *(ptr2 + j));


		}
	}
	for (int i = 0; i < size; i++)
		cout << *(ptr2 + i) << " ";
	cout << endl;
}
void ptr_to_function4(int* ptr, int size) { //basic
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (*(ptr+i)<*(ptr+j))
				swap(*(ptr + i), *(ptr + j));
		}
	}
	for (int i = 0; i < size; i++)
		cout << *(ptr + i) << " ";
	cout << endl;
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

void ptr_to_function2(int* ptr3, int size) { //poli
	menor m;
	valores* v = &m;

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
	for (int i = 0; i < size; i++)
		cout << *(ptr3 + i) << " ";
	cout << endl;
}


int main()
{
	int tam, temp = 0;
	int nt = thread::hardware_concurrency();
	cout << nt << "\n\n\n";
	clock_t t1, t2, t3, t4, t5, t6,t7,t8;
	float diff;
	cout << "ingrese el tamaño de su array: ";
	cin >> tam;
	int* ptr = new int[tam];
	int* ptr2 = new int[tam];
	int* ptr3 = new int[tam];
	int* ptr4 = new int[tam];


	rellenar(tam, ptr);
	copiar(ptr, ptr2, ptr3, ptr4, tam);
	while (temp != 1 && temp != 2)
	{
		cout << "ingrese 1 para oredenar de menor a mayor, 2 para oredenar de mayor a menos: ";
		cin >> temp;
		if (temp == 1)
		{
			t1 = clock();
			cout << "\nOrdenada con el metodo de puntero a funcion\n";
			ptr_to_function(ptr, tam, menorAmayor);
			t2 = clock();
			diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;

			t3 = clock();
			cout << "Ordenada con el metodo de polimorfismo\n";
			ptr_to_function2(ptr3, tam);
			t4 = clock();
			diff = ((float)t4 - (float)t3) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;

			t5 = clock();
			cout << "Ordenada con el metodo de Functor\n";
			ptr_to_function1< Less > (ptr2, tam);
			t6 = clock();
			diff = ((float)t6 - (float)t5) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;

			t7 = clock();
			cout << "Ordenada basica\n";
			ptr_to_function4(ptr, tam);
			t8 = clock();
			diff = ((float)t8 - (float)t7) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;

			break;
		}
		if (temp == 2)
		{
			t1 = clock();
			cout << "\nOrdenada con el metodo de puntero a funcion\n";
			ptr_to_function(ptr, tam, mayorAmenor);
			t2 = clock();
			diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;

			t3 = clock();
			cout << "Ordenada con el metodo de polimorfismo\n";
			ptr_to_function2(ptr3, tam);
			t4 = clock();
			diff = ((float)t4 - (float)t3) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;

			t5 = clock();
			
			cout << "Ordenada con el metodo de Functor\n";
			ptr_to_function1<Greater>(ptr2, tam);
			t6 = clock();
			diff = ((float)t6 - (float)t5) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;
			break;
		}
			
		if (temp == 3)
		{
			
			thread th1= thread(ptr_to_function, ptr, tam, mayorAmenor);
			


			t1 = clock();
			cout << "\nOrdenada con el metodo de puntero a funcion\n";
			thread th2 = thread(ptr_to_function2, ptr3, tam);
			
			th1.join();
			t2 = clock();
			diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;


			t3 = clock();
			cout << "Ordenada con el metodo de polimorfismo\n";
			th2.join();
			t4 = clock();
			diff = ((float)t4 - (float)t3) / CLOCKS_PER_SEC;
			cout << "Running time: " << diff << endl;
			break;
			//thread th3 = thread(ptr_to_function1, ptr2, tam, a);
		}
	}
}
