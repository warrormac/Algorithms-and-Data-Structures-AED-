#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class Nodo
{
public:
	int valor;
	Nodo* next;
	Nodo* prev;
	Nodo(int _valor, Nodo* _next = NULL, Nodo* _prev = NULL)
	{
		valor = _valor;
		next = _next;
		prev = _prev;
	}
	~Nodo()
	{
		next = 0;
		prev = 0;
	}

};


class Lista
{
public:
	Nodo* head;


	Lista()
	{
		head = NULL;
	}
	Lista(int valor, Nodo* prev = 0, Nodo * next = 0)
	{
		head = new Nodo(valor);
		head->next = head;
		head->prev = head;
	}

	bool Buscar(int valor)
	{
		if (head != 0)
		{
			return 1;
		}
		Nodo* temp = head;
		do
		{
			if (temp->valor == valor)
			{
				return 0;
			}
			temp = temp->next;
		} while (temp != head);
		return 1;
	}


	void Agregar(int valor, Nodo* next = 0)
	{
		if (head == 0)
		{
			head = new Nodo(valor);
			head->next = head;
			head->prev = head;
			return;
		}
		else if (Buscar(valor))
		{
			Nodo* temp = head;

			do
			{
				if (temp->valor < valor)
				{

					if (temp->next == head) //FINAL
					{
						temp->next = new Nodo(valor, temp);
						temp->next->next = head;
						head->prev = temp->next;
						temp->next->prev = temp;
						break;
					}

					else if ((temp->next->valor) > valor) //MEDIO
					{
						temp->next = new Nodo(valor, temp->next, temp);
						temp->next->next->prev = temp->next;
						break;
					}
				}
				else//INICIO
				{
					Nodo* last = head;
					while (last->next != head)
					{
						last = last->next;
					}
					head = new Nodo(valor, last, temp);
					temp->next->prev = temp;
					temp->prev = head;
					last->next = head;
					break;
				}
				temp = temp->next;
			} while (temp != head);
		}

	}

	void Eliminar(int valor)
	{
		if (Buscar(valor) and head != 0)
		{
			Nodo* temp = head;

			if (head->valor == valor)
			{

				if (head == head->next)
				{
					delete head;
					head = NULL;
					return;
				}

				Nodo* last = head;
				while (last->next != head)
				{
					last = last->next;
				}
				Nodo* headSgt = head->next;
				delete head;
				head = headSgt;
				head->prev = last;

				last->next = head;
				return;
			}
			temp = temp->next;
			while (temp != head)
			{

				if (temp->next == head)          //FINAL
				{
					temp->prev->next = head;
					head->prev = temp->prev;
					delete temp;
					return;
				}

				if (temp->valor == valor)        //MEDIO
				{
					(temp->prev)->next = temp->next;
					(temp->next)->prev = temp->prev;
					delete temp;
					return;
				}
				temp = temp->next;
			}
		}
	}


	~Lista()
	{
		if (head != 0)
		{
			Nodo* temp = head;
			while (temp)
			{
				Nodo* next = temp->next;
				delete temp;
				temp = next;
			}
		}

	}


	void Imprimir()
	{
		if (head != 0)
		{
			Nodo* temp = head;

			do
			{
				if (temp->prev)
				{
					cout << temp->prev->valor << " <- ";
				}
				else
				{
					cout << "       ";
				}
				cout << temp->valor;
				if (temp->next)
				{
					cout << " -> " << temp->next->valor;
				}
				cout << endl;
				temp = temp->next;


			} while (temp != head);

		}


	}
	void josephus(int n, int k_muertes)
	{
		int Nmuertos = 0;
		for (int i = 1; i <= n; i++)
			Agregar(i);

		cout << "CIRCULO DE HOMBRES: " << endl;
		Imprimir();
		Nodo* ptr = head; Nodo* prev = head;
		while (Nmuertos < n)
		{
			for (int i = 0; i < k_muertes - 1; i++)
				ptr = ptr->next;
			while (prev->next != ptr)
				prev = prev->next;
			if (ptr == head)
				head = head->next;
			prev->next = ptr->next;
			// delete ptr;
			ptr = prev->next;
			Nmuertos++;
		}
		cout << "\n";
		cout << "Posicion de Josephus: "; Imprimir();
		cout << "\n";

	}


};

int main()
{

	Lista* lista = new Lista();
	lista -> Agregar(1);
	lista -> Agregar(2);
	lista -> Agregar(6);
	lista -> Agregar(4);
	lista -> Agregar(7);
	lista->Imprimir();
	cout << endl;
    lista -> Eliminar(1);
	lista -> Eliminar(6);
    lista -> Eliminar(7);
	lista->Imprimir();
	
	/*cout << "      CIRCULAR LIST WHIT DOUBLE POINTER" << endl;
	cout << "\n";
	int n, k;
	cout << " --------THE JOSEPHUS GAME--------" << endl;
	cout << "\n";
	cout << "OH NO!! LOS JUDIOS ESTAN ATRAPADOS POR EL EJERCITO ROMANO" << endl;
	cout << "AYUDALOS A MORIR CON HONOR, SALVO AL BUEN JOSEPHUS CLARO..." << endl;
	cout << "\n";
	cout << "CUANTOS VALIENTES SON? "; cin >> n;
	cout << "SE MATAN CADA? "; cin >> k;
	lista->josephus(n, k);*/


	system("pause");
	system("cls");



	return 0;
}