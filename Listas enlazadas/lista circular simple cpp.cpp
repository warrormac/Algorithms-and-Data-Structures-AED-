#include <iostream>

using namespace std;


class Nodo
{
public:
	int dato;
	Nodo* siguiente;

	Nodo** lista = new Nodo * ();
	Nodo* aux4 = 0;
	Nodo* temp;
	Nodo* temp2;
	Nodo* aux3 = 0;
};


class listas : public Nodo {
public:

	Nodo* actual = new Nodo();
	Nodo* aux_borrar;
	Nodo* anterior = NULL;


	void menu()
	{
		int opcion, dato, i = 0, r = 0;
		int arr[1000];
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
				//cin >> i;

				insertarLista(lista, dato);
				cout << "\n";
				system("pause");
				break;
			case 2:  mostrarLista(lista, i);
				cout << "\n";
				system("pause");
				break;
			case 3: cout << "Ingrese un numero a buscar: ";
				cin >> dato;
				buscarLista(lista, dato);
				cout << "\n";
				system("pause");
				break;
			case 4: cout << "Ingrese el elemento que desea eliminar: ";
				cin >> dato;
				eliminarNodo(lista, dato);
				cout << "\n";
				system("pause");

			}
			system("cls");
		} while (opcion != 5);
	}

	void insertarLista(Nodo**& lista, int n)
	{
		Nodo* nuevo_nodo = new Nodo();
		nuevo_nodo->dato = n;

		Nodo* aux1 = *lista;
		Nodo* aux2 = 0;

		while ((aux1 != NULL) && (aux1->dato < n)) //Para siempre tener ordenada la lista
		{
			aux2 = aux1;
			aux1 = aux1->siguiente;
		}
		(*lista == aux1) ? *lista = nuevo_nodo : aux2->siguiente = nuevo_nodo;
		nuevo_nodo->siguiente = aux1;
		cout << "Elemento " << n << " insertado a la lista correctamente" << endl;
	}


	

	void mostrarLista(Nodo** lista, int r)
	{

		actual = *lista;
		int i = 0;

		while (actual != NULL)
		{
			if (i == 0)
			{
				aux4 = actual;
			}
			cout << actual->dato << " -> ";
			actual = actual->siguiente;
			i++;

		}


	}

	bool buscarLista(Nodo**& lista, int n)
	{
		bool band = false;
		Nodo* actual = new Nodo();
		actual = *lista;

		while ((actual != NULL) && (actual->dato <= n))
		{
			if (actual->dato == n)
			{
				band = true;
				while ((aux_borrar != NULL) && (aux_borrar->dato != n))
				{
					anterior = aux_borrar;
					aux_borrar = aux_borrar->siguiente;
				}
			}
			actual = actual->siguiente;
		}
		if (band == true)
		{
			cout << "El Elemento " << n << " Si ha sido encontrado en la lista";
			return 1;
		}
		else {
			cout << "El Elemento " << n << " No ha sido encontrado en la lista";
			return 0;
		}
	}

	void eliminarNodo(Nodo**& lista, int n)
	{
		if (lista != NULL)
		{

			aux_borrar = *lista;
			buscarLista(lista, n);
			if (n == (*lista)->dato)
			{
				temp2 = temp2->siguiente;
			}
			if (anterior == NULL) {
				*lista = (*lista)->siguiente;
				delete aux_borrar;
			}
			else {
				anterior->siguiente = aux_borrar->siguiente;
				delete aux_borrar;
			}
		}
		if (n == aux4->dato) {
			aux4 = aux4->siguiente;
			temp = aux4;
		}

	}

};

/////////////////////////////////////////////////////////////////////////

int main()
{

	Nodo aaa;
	listas obj1;
	obj1.menu();

	return 0;

}