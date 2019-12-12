#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}

// main function to do heap sort 
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		heapify(arr, i, 0);
	}
}

void borrar(int* ptr, int &tam)
{
	if (tam == NULL)
		return;
	tam--;
	int* ptr2 = new int[tam];
	for (int i = 0; i < tam; i++)
	{
		 ptr[i]=ptr[i+1];
	}
	
}
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

void menu(int *&ptr,int tam)
{
	heapSort(ptr, tam);
	int opcion, dato;
	
	do {
		cout << "\t         MENU   \n";
		cout << "1. Mostrar los elementos de la lista\n";
		cout << "2. Eliminar un Nodo de la Lista\n";
		cout << "5. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1: 
			printArray(ptr, tam);
			cout << "\n";
			system("pause");
			break;
		
		case 2: 
			borrar(ptr, tam);
			cout << "\n";
			system("pause");

		}
		system("cls");
	} while (opcion != 5 || tam!=NULL);
}

void rellenar(int tam, int* &ptr)
{
	int temp,temp2=0;
	while (temp2<tam)
	{
		cout << "ingrese su elemnto: ";
		cin >> temp;

		ptr[temp2] = temp;
		temp2++;
	}
}

int main()
{
	int tam;
	cout << "ingrese el tamaño su array:";
	cin >> tam;
	int* ptr = new int[tam];
	rellenar(tam, ptr);
	menu(ptr,tam);
	delete ptr;
}