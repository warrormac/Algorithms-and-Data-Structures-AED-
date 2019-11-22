#include <iostream>
#include <list>
#include <math.h>
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
		return a < b;
	}
};


template <class T, class O>
struct Tree
{
	Node<T>* n_root;
	O Compare;
	Tree() { n_root = 0; }
	~Tree() {};
	Tree* prev;
	string str;

	Tree(Tree* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
	bool Find(T x, Node<T>**& p);
	bool Insert(T x);
	bool Delete(T x);
	Node<T>** rep(T x, Node<T>** p);
	void showTrunks(Tree* p);
	void printTree(Node<T>* root, Tree* prev, bool isLeft);

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


template<class T>
class Nodes {
public:
	Nodes(T);
	Nodes<T>* sons[3]; // 0 Izquierdo 1 Derecho 2 padre
	T data;
};

template<class T>
Nodes<T>::Nodes(T _data) {
	data = _data;
	sons[0] = sons[1] = nullptr;
}

template<class T>
void treeBuild(Nodes<T>*& head, Nodes<T>* nodeArray[100], int counter);

template<class T>
void Heapify(Nodes<T>* node1, Nodes<T>* node2, Nodes<T>* head);

//template<class T>
//void printTree(Nodes<T>* head, int space);



template<class T>
void treeBuild(Nodes<T>*& head, Nodes<T>* nodeArray[200], int counter) {
	for (int i = 1; i < counter + 1; i++) {
		//establecemos el indice en la raiz del arbol
		if (i == 1) {
			head = nodeArray[i];
		}
		else {
			//Cantidad de nodos y los dividimos entre 2 
			int parent = -1;
			parent = round(i / 2);
			//Si el padre no tiene hijo izquierdo balanceamos 
			if (nodeArray[parent]->sons[0] == NULL) {
				;
				nodeArray[parent]->sons[0] = nodeArray[i];
				nodeArray[i]->sons[2] = nodeArray[parent];
				Heapify(nodeArray[parent], nodeArray[i], head);
			}
			//Si el papa tiene hijo izquierdo insertamos en el hijo derecho y balanceamos
			else {
				nodeArray[parent]->sons[1] = nodeArray[i];
				nodeArray[i]->sons[2] = nodeArray[parent];
				Heapify(nodeArray[parent], nodeArray[i], head);
			}
		}
	}
}

template<class T>
void Heapify(Nodes<T>* node1, Nodes<T>* node2, Nodes<T>* head) {
	//Si el primer nodo es mas grande que el primero swapeamos
	if (node2->data > node1->data) {
		T temp = node2->data;
		node2->data = node1->data;
		node1->data = temp;
		//si no es la raiz recursividad forever :v 
		if (node1->data != head->data) {
			Heapify(node1->sons[2], node2->sons[2], head);
		}
	}
}

template<class T, class O>
void Tree<T, O>::showTrunks(Tree* p)
{
	if (p == nullptr)
		return;

	showTrunks(p->prev);

	cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
template<class T, class O>
void Tree<T, O>::printTree(Node<T>* root, Tree* prev, bool isLeft)
{
	if (root == nullptr)
		return;

	string prev_str = "    ";
	Tree* trunk = new Tree(prev, prev_str);

	printTree(root->N_nodes[0], trunk, true);

	if (!prev)
		trunk->str = "---";
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else
	{
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << root->n_x << endl;

	if (prev)
		prev->str = prev_str;
	trunk->str = "   |";

	printTree(root->N_nodes[1], trunk, false);
}
struct Trunk
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk* p)
{
	if (p == nullptr)
		return;

	showTrunks(p->prev);

	cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
template<class T>
void printsTree(Nodes<T>* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr)
		return;

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printsTree(root->sons[0], trunk, true);

	if (!prev)
		trunk->str = "---";
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else
	{
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << root->data << endl;

	if (prev)
		prev->str = prev_str;
	trunk->str = "   |";

	printsTree(root->sons[1], trunk, false);
}
void queue(list<int> lista, int size)
{
	Tree<int, Less<int> > temp;
	Nodes<int>* nodeArray[100];
	int* numbers = new int[200];
	int k = 0;
	for (int const& i : lista) {
		numbers[k++] = i;
	}
	int counter = 10;
	Nodes<int>* head; //= new Node(NULL)



	nodeArray[0] = NULL;

	for (int i = 0; i < size; i++) {
		Nodes<int>* newNode = new Nodes<int>(numbers[i]);
		nodeArray[i + 1] = newNode;
	}

	treeBuild(head, nodeArray, size);
	printsTree(head, nullptr, false);
}


int main()
{
	int menu = 0;
	int num,size=0;
	Tree<int, Less<int> > Ent;
	Tree<int, Less<int> > Ent2;
	list<int>lista;
	while (menu != 5)
	{
		cout << "ingrese 1 para ingresasr numeros\ningrese 2 para mostrar el arbol\ningrese 3 para eliminar un elemnto\ningrese 5 para EXIT: ";
		cin >> menu;
		while (menu < 1 && menu>5 && menu == 4)
		{
			cout << "opcion no valida: ";
			cin >> menu;
		}
		if (menu == 1)
		{
			cout << "ingrese el numero: ";
			cin >> num;
			Ent.Insert(num);
			lista.push_back(num);
			size++;
			system("pause");
		}
		if (menu == 2)
		{
			Ent.printTree(Ent.n_root, nullptr, false);
			queue(lista, size);

		}
		cout << "\n\n\n";
	}
	
}


-----------------------------------------------------------------------------------------
	
