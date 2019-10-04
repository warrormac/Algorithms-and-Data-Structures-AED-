#include <iostream>

using namespace std;
class Nodo
{
public:
	int dato;
	Nodo* siguiente;
	Nodo* anterior;
	Nodo* lista2 = NULL;
	Nodo* ultimo = NULL;
	
};
Nodo** lista = new Nodo * ();
Nodo* Lista = NULL;
Nodo* actual = new Nodo();

class listas : public Nodo {
public:
	Nodo* aux_borrar;
	void menu()
	{
		int opcion, dato;
		do {
			cout << "\t         MENU   \n";
			cout << "1. Insertar elementos en la lista\n";
			cout << "2. Mostrar los elementos de la lista\n";
			cout << "3. Eliminar un Nodo de la Lista\n";
			cout << "5. Salir\n";
			cout << "Opcion: ";
			cin >> opcion;

			switch (opcion)
			{
			case 1:
				cout << "Ingresa un numero: " << endl;
				cin >> dato;
				insertarLista(Lista, dato);
				cout << "\n";
				system("pause");
				*lista = Lista;
				break;
			case 2:  mostrarLista(lista);
				cout << "\n";
				system("pause");
				break;
			case 3: cout << "Ingrese el elemento que desea eliminar: ";
				cin >> dato;
				eliminarNodo(lista, dato);
				cout << "\n";
				system("pause");
			}
			system("cls");
		} while (opcion != 5);
	}

	void insertarLista(Nodo*& lista, int n)
	{
		if (lista == NULL) {
			Nodo* nuevo_nodo = new Nodo();
			nuevo_nodo->dato = n;
			nuevo_nodo->siguiente = nuevo_nodo->anterior = nuevo_nodo;
			lista = nuevo_nodo;

			cout << "Elemento " << n << " insertado a la lista correctamente" << endl;
		}
		else {
			Nodo* ultimo = lista->anterior;
			Nodo* nuevo_nodo = new Nodo();
			nuevo_nodo->dato = n;

			nuevo_nodo->siguiente = lista;
			lista->anterior = nuevo_nodo;
			nuevo_nodo->anterior = ultimo;
			ultimo->siguiente = nuevo_nodo;
			cout << "Elemento " << n << " insertado a la lista correctamente" << endl;
		}
		
	}
	void mostrarLista(Nodo** lista)
	{
		Nodo* aux = *lista;
		cout << "Del primero al ultimo" << endl;
		while (aux->siguiente != *lista) {
			cout << aux->dato << "->";
			aux = aux->siguiente;
		}
		cout << aux->dato << "->" << endl;

		cout << "Del ultimo al primero" << endl;
		Nodo* ultimo = (*lista)->anterior;
		aux = ultimo;
		while (aux->anterior != ultimo) {
			cout << aux->dato << "<-";
			aux = aux->anterior;
		}
		cout << aux->dato << "<-";
	}

	void buscar(Nodo** lista, int n) {
		if (buscarLista(lista, n) == NULL)
			cout << "El Elemento " << n << " No ha sido encontrado en la lista";
		else
			cout << "El Elemento " << n << " Si ha sido encontrado en la lista";
	}


	Nodo* buscarLista(Nodo** lista, int n)
	{
		bool esta = false;
		Nodo* actual = *lista;
		while (actual->siguiente != *lista) {
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
	void eliminarNodo(Nodo**& lista, int n)
	{
		Nodo* nodo = buscarLista(lista, n);
		if (nodo == NULL)
			cout << "el elemento no ha sido encontrado";
		else {
			if (nodo == *lista) 
				*lista = nodo->siguiente;
			Nodo* ant_nodo = nodo->anterior;
			Nodo* sig_nodo = nodo->siguiente;
			ant_nodo->siguiente = sig_nodo;
			sig_nodo->anterior = ant_nodo;
			cout << "el elemento ha sido eliminado";
			mostrarLista(lista);
		}

	}

};


int main()
{

	Nodo aaa;
	listas obj1;
	obj1.menu();

	return 0;

}