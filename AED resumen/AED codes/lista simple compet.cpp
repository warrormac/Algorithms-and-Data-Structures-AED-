#include <iostream>
#include <set>
#include <algorithm> 
#include <unordered_set>
using namespace std;


void insertar(list<int>& lista, int n)
{
	list<int>::iterator itr = lista.end();
	lista.insert(itr, n);
}
void mostrarLista(list<int>& lista)
{
	list<int>::iterator itr;
	for (itr = lista.begin(); itr != lista.end(); itr++)
		cout << *itr << " ";
}
void buscarLista(list<int>& lista, int n, int r)
{
	list<int>::iterator itr;
	itr = find(lista.begin(), lista.end(), n);
	if (itr != lista.end())
	{
		cout << "el elemento se encontro\n";
		if (r == 1)
			lista.erase(itr);
	}
	else
		cout << "el elemento no se encontro\n";
}
void borrar(list<int>& lista, int n)
{
	buscarLista(lista, n, 1);
}
void menu(list<int>& lista)
{
	int opcion, dato;
	do {
		cout << "\t         MENU   \n";
		cout << "1. Insertar elementos en la lista\n";
		cout << "2. Mostrar los elementos de la lista\n";
		cout << "3. Buscar un elemento en lista\n";
		cout << "4. Eliminar un Nodo de la Lista\n";
		cout << "5. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			cout << "Ingresa un numero: " << endl;
			cin >> dato;
			insertar(lista, dato);
			cout << "\n";
			system("pause");
			break;
		case 2:  mostrarLista(lista);
			cout << "\n";
			system("pause");
			break;
		case 3: cout << "Ingrese un numero a buscar: ";
			cin >> dato;
			buscarLista(lista, dato, 0);
			cout << "\n";
			system("pause");
			break;
		case 4: cout << "Ingrese el elemento que desea eliminar: ";
			cin >> dato;
			borrar(lista, dato);
			cout << "\n";
			system("pause");

		}
		system("cls");
	} while (opcion != 5);
}

int main()
{
	list<int>lista;
	menu(ref(lista));
}