#include <iostream>
#include <stdio.h>
#include <list>

using namespace std;

template <class T>
struct Node
{
	Node(T x)
	{
		N_nodes[0] = NULL; // HIJO IZQUIERDO
		N_nodes[1] = NULL; // HJO DERECHO
		n_x = x;
		
	}
	Node<T>* N_nodes[2];
	T n_x;

};

template<class T>
struct Less
{
	inline bool operator()(T a, T b)
	{
		return a > b;
	}
};


template <class T, class O>
struct Tree
{
	Node<T>* n_root;
	O Compare;
	Tree() { n_root = 0; }
	~Tree() {};
	bool Find(T x, Node<T>**& p);
	bool Insert(T x);
	bool Delete(T x);
	Node<T>** rep(T x, Node<T>** p);
	void InOrden(Node<T>* p);
	void postorder(Node<T>* p);
	void preorder(Node<T>* p);


};

template<class T, class O>
Node<T>** Tree<T, O>::rep(T x, Node<T>** p)
{
	for (p = &((*p)->N_nodes[0]); *p && (*p)->N_nodes[1]; p = &((*p)->N_nodes[Compare((*p)->n_x, x)]));//MAYOR DE LOS MENORES
	return p; // DIRECCION DEL NODO IZQ
}

template<class T, class O>
bool Tree<T, O>::Find(T x, Node<T>**& p)
{
	for (p = &n_root; *p and (*p)->n_x != x; p = &((*p)->N_nodes[Compare((*p)->n_x, x)]));
	return !!*p;
}

template<class T, class O>
bool Tree<T, O>::Insert(T x)
{
	Node<T>** p;
	if (Find(x, p)) return 0;
	*p = new Node<T>(x);
	return 1;
}
template<class T, class O>
bool Tree<T, O>::Delete(T x)
{
	Node<T>** p;
	if (!Find(x, p)) return 0;
	if ((*p)->N_nodes[0] and (*p)->N_nodes[1])//TIENE DOS HIJOS
	{
		Node<T>** q = rep(x, p);
		(*p)->n_x = (*q)->n_x;
		p = q;
	}
	Node<T>* temp = *p;
	*p = (*p)->N_nodes[(*p)->N_nodes[1] != 0];
	delete temp;
	return 1;

}
template<class T, class O>
void Tree<T, O>::preorder(Node<T>* p)
{
	
	if (!p) return;
	cout << p->n_x << " <<->> ";
	preorder(p->N_nodes[0]);
	preorder(p->N_nodes[1]);

}
void heapify(int arr[], int n, int i)
{
	int smallest = i; // Initialize smalles as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 
	if (l < n && arr[l] < arr[smallest])
		smallest = l;
	if (r < n && arr[r] < arr[smallest])
		smallest = r;
	if (smallest != i) {
		swap(arr[i], arr[smallest]);
		heapify(arr, n, smallest);
	}
}
void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
/*void heapify(int arr[], int n, int i)
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
}*/

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}


void ingresar(Tree<int, Less<int> > Ent,int *size, list<int>& lista,int a)
{
	cout << a << "\n";
	Ent.Insert(a);
	(*size)++;
	list<int>::iterator itr = lista.end();
	lista.insert(itr, a);
	

}
void menu( int *size)
{
	
	Tree<int, Less<int> > Ent; Tree<int, Less<int> > Ent2;
	list<int>lista;
	int opcion, dato;

	do {
		cout << "\t         MENU   \n";
		cout << "1. ingresa elementos a tu arbol\n";
		cout << "2. aplicar prioridad\n";
		cout << "5. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			int a;
			cout << "ingrese su numero: ";
			cin >> a;
			ingresar(Ent, size, lista, a);
			cout << "\n";
			
			system("pause");
			break;

		case 2:
			
			int* ptr = new int[*size];
			int k = 0;
			for (int const& i : lista) {
				ptr[k++] = i;
			}
			
			heapSort(ptr, *size);
			printArray(ptr, *size);			

			int itr=0;
			for (itr;itr<*size;itr++)
			{
				Ent.Delete(ptr[itr]);
				cout << itr<<"\n";
				Ent2.Insert(ptr[itr]);
			}
			Ent2.preorder(Ent2.n_root);

			cout << "\n";
			system("pause");

		}
		system("cls");
	} while (opcion != 5 );
}

int main()
{
	int tam = 0;
	int* size = &tam;
	menu(size);

}