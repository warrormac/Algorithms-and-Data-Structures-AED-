#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;
class Nodo
{
public:

	int dato;
	Nodo* siguiente;
	Nodo* anterior;

	Nodo* lista = NULL;

};

class listas :public Nodo {

public:

	void menu()
	{
		int kill = 0, people = 0, op;
		cout << "ingrese cuantas personas estan:  ";
		cin >> people;

		cout << "ingrese cada cuanto quiere que se maten:  ";
		cin >> kill;

		cout << "ingresa 1 para eliminar de izquierda a derecha,  2 para eleminar de derecha a izquierda: ";
		cin >> op;
		int cont = 1;
		int opcion, dato, i = 1, r = 0, p = 0;

		while (cont <= people)
		{
			r = insertarLista(lista, cont, r);
			cont++;
		}
		int killer = lista->dato;

		if (op == 1)
		{
			while (people > 2)
			{
				if (i == kill)
				{
					mostrarLista(lista);
					killer = lista->dato;
					people = eliminarNodo(lista, killer, people);
					i = 1;

				}
				lista = lista->siguiente;
				i++;
			}
		}
		if (op == 2)
		{
			while (people > 2)
			{
				if (i == kill + 1)
				{
					mostrarLista(lista);
					killer = lista->dato;
					people = eliminarNodo(lista, killer, people);
					i = 1;

				}
				lista = lista->anterior;
				i++;
			}
		}
		mostrarLista(lista);
	}

	int insertarLista(Nodo*& lista, int n, int r)
	{
		if (lista == NULL) {
			Nodo* nuevo_nodo = new Nodo();
			nuevo_nodo->dato = n;
			nuevo_nodo->siguiente = nuevo_nodo->anterior = nuevo_nodo;
			lista = nuevo_nodo;

			//cout << "Elemento " << n << " insertado a la lista correctamente" << endl;
		}
		else {
			Nodo* ultimo = lista->anterior;
			Nodo* nuevo_nodo = new Nodo();
			nuevo_nodo->dato = n;

			nuevo_nodo->siguiente = lista;
			lista->anterior = nuevo_nodo;
			nuevo_nodo->anterior = ultimo;
			ultimo->siguiente = nuevo_nodo;

		}
		r++;
		return r;
	}
	void mostrarLista(Nodo* lista)
	{
		Nodo* aux = lista;

		while (aux->siguiente != lista) {
			cout << aux->dato << "->";
			aux = aux->siguiente;
		}
		cout << aux->dato << "->" << endl;
	}

	void buscar(Nodo* lista, int n) {
		if (buscarLista(lista, n) == NULL)
			cout << "";
		else
			cout << "";
	}

	Nodo* buscarLista(Nodo* lista, int n)
	{
		bool esta = false;
		Nodo* actual = lista;
		while (actual->siguiente != lista) {
			//cout << "ok" << endl;
			if (actual->dato == n) {
				return actual;
			}
			actual = actual->siguiente;
		}
		if (actual->dato == n) {
			return actual;
		}
		else {
			return NULL;
		}
	}
	int eliminarNodo(Nodo*& lista, int n, int people)
	{
		Nodo* nodo = buscarLista(lista, n);
		if (nodo == NULL) {
			//cout << "el elemento no ha sido encontrado";
		}
		else {
			if (nodo == lista) {
				lista = nodo->siguiente;
			}
			Nodo* ant_nodo = nodo->anterior;
			Nodo* sig_nodo = nodo->siguiente;
			ant_nodo->siguiente = sig_nodo;
			sig_nodo->anterior = ant_nodo;
			cout << "\n" << n << " ha sido eliminado" << endl;;
		}
		people--;
		return people;
	}
};

int main()
{
	Nodo caller;
	listas call;
	call.menu();
	return 0;
}