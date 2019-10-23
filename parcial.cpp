#include <iostream>
#include <set>
#include <algorithm> 
#include <unordered_set>
using namespace std;

template <class T>
struct Node {
	T val;
	Node* next;
	Node(T x, Node<T>* nxt) {
		val = x;
		next = nxt;
	}
};

template <class T>
class CircLL {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	CircLL();
	bool buscar(Node<T>**& p, Node<T>*& prev, T x);
	bool insertar(T x);
	bool borrar(T x);
	void imprimir();
};

template <class T>
CircLL<T>::CircLL() {
	this->head = 0;
	this->tail = 0;
}

template <class T>
bool CircLL<T>::buscar(Node<T>**& p, Node<T>*& prev, T x) {
	p = &head;
	if (*p && (*p)->next && (*p)->val < x) p = &(*p)->next;
	for (*p; *p && (*p)->val < x && *p != head; prev = *p, p = &(*p)->next);
	return (*p && (*p)->val == x);
}

template <class T>
bool CircLL<T>::insertar(T x) {
	Node<T>** p, * prev;
	if (buscar(p, prev, x)) return 0;
	*p = new Node<T>(x, *p);
	if (!((*p)->next)) {
		(*p)->next = head;
		tail = *p;
	}
	if ((*p)->next == head) {
		tail = *p;
	}
	tail->next = head;
	return 1;
}

template <class T>
bool CircLL<T>::borrar(T x) {
	Node<T>** p, * prev;
	if (!buscar(p, prev, x)) return 0;
	Node<T>* temp = (*p)->next;
	if (*p == tail) {
		tail = prev;
	}
	delete* p;
	*p = temp;
	tail->next = head;
}

template <class T>
void CircLL<T>::imprimir() {
	Node<T>* t = head;
	bool aux = 1;
	while ((t) && (t != this->head || aux)) {
		cout << (t)->val << " ";
		t = (t)->next;
		aux = 0;
	}
	cout << (t)->val << " ";
	cout << endl;
}

void insertar(list<int>& lista, int n)
{
	list<int>::iterator itr = lista.end();
	lista.insert(itr, n);
	lista.sort();
}
bool buscarLista(list<int>& lista, int n, int r)
{
	list<int>::iterator itr;
	itr = find(lista.begin(), lista.end(), n);
	if (itr != lista.end())
	{
		//cout << "el elemento se encontro\n";
		if (r == 1)
			lista.erase(itr);
		return 1;
	}
	else {
		//cout << "el elemento no se encontro\n";
		return 0;
	}
}
void Borrar(list<int>& lista, int n)
{
	buscarLista(lista, n, 1);
}
void mostrarLista(list<int>& lista)
{

	int boo = 0, cont = 0;
	bool a;
	list<int>lista2;
	list<int>temp(lista.begin(), lista.end());
	list<int>::iterator itr;
	list<int>::iterator itr2;
	list<int>::iterator itr3;



	for (itr = lista.begin(); itr != lista.end(); itr++)
	{

		CircLL<int> A;
		for (itr2 = next(temp.begin(), cont); itr2 != temp.end(); itr2++)
		{
			if (*itr2 % *itr == 0)
			{
				if (boo == 0)
				{

					A.insertar(*itr);
					boo++;
				}

				else {
					A.insertar(*itr2);
					if (*itr2 != *itr)
						insertar(lista2, *itr2);
				}

			}

		}
		itr3 = itr;
		a = buscarLista(lista2, *itr3, 0);
		if (a == 1)
			;
		else {
			cout << *itr << "\---";
			A.imprimir();
			boo = 0;
			cont++;
		}


	}
	itr2 = lista2.begin();
	for (itr = lista.begin(); itr != lista.end() && itr2 != lista2.end(); itr++, itr2++)
	{
		Borrar(lista, *itr2);
	}
	//for (itr = lista.begin(); itr != lista.end(); itr++)       para borrar los multiplos
		//cout << *itr << " ";

}



void menu(list<int>& lista)
{
	int opcion, dato;
	do {
		cout << "\t     Examen Parcial  \n";
		cout << "Nombre:Andre Alvarez          Grupo:CCOMP4-1.2  \n\n";
		cout << "\t         MENU   \n";
		cout << "1. Insertar elementos en la lista\n";
		cout << "2. Mostrar los elementos de la lista\n";

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


		}
		system("cls");
	} while (opcion != 5);
}

int main()
{
	list<int>lista;
	menu(ref(lista));
}

-------------------------------------------------------
#include <iostream>
#include <set>
#include <list>
#include <algorithm> 
#include <unordered_set>
using namespace std;

template <class T>
struct Node {
	T val;
	Node* next;
	Node(T x, Node<T>* nxt) {
		val = x;
		next = nxt;
	}
};

template <class T>
class CircLL {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	CircLL();
	bool buscar(Node<T>**& p, Node<T>*& prev, T x);
	bool insertar(T x);
	bool borrar(T x);
	void imprimir();
};

template <class T>
CircLL<T>::CircLL() {
	this->head = 0;
	this->tail = 0;
}

template <class T>
bool CircLL<T>::buscar(Node<T>**& p, Node<T>*& prev, T x) {
	p = &head;
	if (*p && (*p)->next && (*p)->val < x) p = &(*p)->next;
	for (*p; *p && (*p)->val < x && *p != head; prev = *p, p = &(*p)->next);
	return (*p && (*p)->val == x);
}

template <class T>
bool CircLL<T>::insertar(T x) {
	Node<T>** p, * prev;
	if (buscar(p, prev, x)) return 0;
	*p = new Node<T>(x, *p);
	if (!((*p)->next)) {
		(*p)->next = head;
		tail = *p;
	}
	if ((*p)->next == head) {
		tail = *p;
	}
	tail->next = head;
	return 1;
}

template <class T>
bool CircLL<T>::borrar(T x) {
	Node<T>** p, * prev;
	if (!buscar(p, prev, x)) return 0;
	Node<T>* temp = (*p)->next;
	if (*p == tail) {
		tail = prev;
	}
	delete* p;
	*p = temp;
	tail->next = head;
}

template <class T>
void CircLL<T>::imprimir() {
	Node<T>* t = head;
	bool aux = 1;
	while ((t) && (t != this->head || aux)) {
		cout << (t)->val << " ";
		t = (t)->next;
		aux = 0;
	}
	cout << (t)->val << " ";
	cout << endl;
}

void insertar(list<int>& lista, int n)
{
	list<int>::iterator itr = lista.end();
	lista.insert(itr, n);
	lista.sort();
}
bool buscarLista(list<int>& lista, int n, int r)
{
	list<int>::iterator itr;
	itr = find(lista.begin(), lista.end(), n);
	if (itr != lista.end())
	{
		//cout << "el elemento se encontro\n";
		if (r == 1)
			lista.erase(itr);
		return 1;
	}
	else {
		//cout << "el elemento no se encontro\n";
		return 0;
	}
}
void Borrar(list<int>& lista, int n)
{
	buscarLista(lista, n, 1);
}
void mostrarLista(list<int>& lista)
{

	int boo = 0, cont = 0;
	bool a;
	list<int>lista2;
	list<int>temp(lista.begin(), lista.end());
	list<int>::iterator itr;
	list<int>::iterator itr2;
	list<int>::iterator itr3;



	for (itr = lista.begin(); itr != lista.end(); itr++)
	{

		CircLL<int> A;
		for (itr2 = next(temp.begin(), cont); itr2 != temp.end(); itr2++)
		{
			if (*itr2 % *itr == 0)
			{
				if (boo == 0)
				{

					A.insertar(*itr);
					boo++;
				}

				else {
					A.insertar(*itr2);
					if (*itr2 != *itr)
						insertar(lista2, *itr2);
				}

			}

		}
		itr3 = itr;
		a = buscarLista(lista2, *itr3, 0);
		if (a == 1)
			;
		else {
			cout << *itr << "\---";
			A.imprimir();
			boo = 0;
			cont++;
		}


	}
	itr2 = lista2.begin();
	for (itr = lista.begin(); itr != lista.end() && itr2 != lista2.end(); itr++, itr2++)
	{
		Borrar(lista, *itr2);
	}
	//for (itr = lista.begin(); itr != lista.end(); itr++)       para borrar los multiplos
		//cout << *itr << " ";

}



void menu(list<int>& lista)
{
	int opcion, dato;
	do {
		cout << "\t     Examen Parcial  \n";
		cout << "Nombre:Andre Alvarez          Grupo:CCOMP4-1.2  \n\n";
		cout << "\t         MENU   \n";
		cout << "1. Insertar elementos en la lista\n";
		cout << "2. Mostrar los elementos de la lista\n";

		cout << "5. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			cout << "Ingresa un numero: " << endl;
			cin >> dato;
			while (dato <= 1)
			{
				cout << "el valor tiene que sera mayor a 1, intente otro valor: ";
				cin >> dato;
			}
			insertar(lista, dato);
			cout << "\n";
			system("pause");
			break;
		case 2:  mostrarLista(lista);
			cout << "\n";
			system("pause");
			break;


		}
		system("cls");
	} while (opcion != 5);
}

int main()
{
	list<int>lista;
	menu(lista);
}
