#include <iostream>
//#include "Nodo.h"
#include <stdlib.h>
using namespace std;

template <class T>
class Nodo {
public:
	T dato;
	Nodo* siguiente;
	Nodo* anterior;

	void insertarLista(Nodo<T>* lista, T n)
	{
		Nodo<T>* nuevo_nodo = new Nodo<T>();
		nuevo_nodo->dato = n;

		Nodo<T>* aux1 = lista;
		Nodo<T>* aux2 = 0;

		while ((aux1 != NULL) && (aux1->dato < n)) //Para siempre tener ordenada la lista
		{
			aux2 = aux1;
			aux1 = aux1->siguiente;
		}
		if (lista == aux1)// se cumple siempre y cuando el elemento que se ingrese al principio de la lista
		{
			//lista = nuevo_nodo;
			lista = nuevo_nodo;
		}
		else //entro al while y corrio una posicion mas
		{
			aux2->siguiente = nuevo_nodo;
		}

		nuevo_nodo->siguiente = aux1;

		cout << "Elemento " << n << " insertado a la lista correctamente" << endl;
	}

	void mostrarLista(Nodo<T>* lista)
	{
		Nodo<T>* actual = new Nodo<T>();
		actual = lista;

		while (actual != NULL) {
			cout << actual->dato << " -> ";
			actual = actual->siguiente;
		}
	}
	void buscarLista(Nodo<T>* lista, T n)
	{
		bool band = false;

		Nodo<T>* actual = new Nodo<T>();
		actual = lista;

		while ((actual != NULL) && (actual->dato <= n))
		{
			if (actual->dato == n)
			{
				band = true;
			}
			actual = actual->siguiente;
		}
		if (band == true)
		{
			cout << "El Elemento " << n << " Si ha sido encontrado en la lista";
		}
		else {
			cout << "El Elemento " << n << " No ha sido encontrado en la lista";

		}
	}
	void eliminarNodo(Nodo<T>* lista, T n)
	{
		//preguntar si la lista no esta vacia
		if (lista != NULL)
		{
			Nodo<T>* aux_borrar;
			Nodo<T>* anterior = NULL;

			aux_borrar = lista;

			//recorrer la lista
			while ((aux_borrar != NULL) && (aux_borrar->dato != n))
			{
				anterior = aux_borrar;
				aux_borrar = aux_borrar->siguiente;
			}

			//El elemento no ha sido encontrado
			if (aux_borrar == NULL) {
				cout << "el elemento no ha sido encontrado";
			}
			//el primer elemento es el que vamos a eliminar
			else if (anterior == NULL) {
				lista = lista->siguiente;
				delete aux_borrar;
			}
			//el elemento esta en la lista pero no es el primer nodo
			else {
				anterior->siguiente = aux_borrar->siguiente;
				delete aux_borrar;
			}
		}
	}
};



template <class T>
void menu(Nodo<T>* lista)
{
	int opcion;
	T dato;
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
			lista->insertarLista(lista, dato);
			cout << "\n";
			//system("pause");
			break;
		case 2:
			lista->mostrarLista(lista);
			cout << "\n";
			//system("pause");
			break;
		case 3:
			cout << "Ingrese un numero a buscar: ";
			cin >> dato;
			lista->buscarLista(lista, dato);
			cout << "\n";
			//system("pause");
			break;
		case 4:
			cout << "Ingrese el elemento que desea eliminar: ";
			cin >> dato;
			lista->eliminarNodo(lista, dato);
			cout << "\n";
			//system("pause");

		}
		//system("cls");
	} while (opcion != 5);
}

int main()
{
	Nodo<char>* list = new Nodo<char>();
	menu(list);

	return 0;
}