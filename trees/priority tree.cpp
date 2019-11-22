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
	int num, size = 0;
	Tree<int, Less<int> > Ent;
	Tree<int, Less<int> > Ent2;
	list<int>lista;
	while (menu != 5)
	{
		cout << "\t         MENU   \n";
		cout << "1. Insertar elementos en el arbol\n";
		cout << "2. Mostrar el arbol\n";
		//cout << "3. Eliminar un Nodo de la Lista\n";
		cout << "5. Salir\n";
		cout << "Opcion: ";
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
		/*if (menu == 3)
		{
			list<int>lista2;
			list<int>::iterator itr2;
			itr2 = lista.begin();
			lista.sort(greater<int>());
			itr2=next(lista.begin(), 1);
			for (; itr2 != lista.end(); itr2++)
				lista2.push_back(*itr2);
			size--;
			queue(lista2, size);
		}*/
		cout << "\n\n\n";
	}

}



-----------------------------------------------------------------------------------------
#include <iostream>
#include <queue>
#include <vector>
#include <Windows.h>
#include <math.h>
#include <string>

using namespace std;

template<class T>
class Mayor {
public:
	bool inline operator()(T a, T b) {
		return a > b;
	}
};

template<class T>
void swap_cuock(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
void gotoxy(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
template<class T>
class PriorityNode {
public:
	T value;
	PriorityNode<T>* P_Nodes[3];
	PriorityNode(T val) {
		value = val;
		P_Nodes[0] = P_Nodes[1] = P_Nodes[2] = 0;
	}
	PriorityNode(T val, PriorityNode<T>* father) {
		value = val;
		P_Nodes[2] = father;
		P_Nodes[0] = P_Nodes[1] = 0;
	}
};

template<class T, class Op>
class PriorityTree {
public:
	PriorityNode<T>* Root;
	unsigned int altura;
	Op o;

	T* data;
	int PriorityCap, PriorityCount, PriorityLast;
	static const int DefaultCap = 50;
	queue<PriorityNode<T>*> colita;
	PriorityTree() {
		Root = 0;
		altura = 0;
		PriorityCap = DefaultCap;
		PriorityCount = PriorityLast = 0;
		resize(PriorityCap);
	}
	PriorityTree(const unsigned int size_i) {
		Root = 0;
		altura = 0;
		PriorityCap = size_i + 1;
		PriorityCount = PriorityLast = 0;
		resize(PriorityCap);
	}
	PriorityNode<T>* AmorComoElNuestro(T val);
	bool insertar_node(PriorityNode<T>*& p, T val);
	bool insertar(T val);
	//bool Extract_Max();
	void print();

	void PrintPerLevel();
	void PrintRight(PriorityNode<T>* p, int cont);
	void PrintAsiNoMame();
	int get_altura(PriorityNode<T>* p);

	void resize(unsigned int new_size);
	bool is_empty();
	unsigned int size();
	unsigned int capacity();
	void recalculate(int iter);
	bool Push(const T& p);
	bool Extract_Max();



};
template<class T, class Op>
PriorityNode<T>* PriorityTree<T, Op>::AmorComoElNuestro(T val)
{
	PriorityNode<T>* NuevoNodoNomame;
	NuevoNodoNomame = new PriorityNode<T>(val);
	return NuevoNodoNomame;
}

template<class T, class Op>
bool PriorityTree<T, Op>::insertar_node(PriorityNode<T>*& p, T val)
{
	if (p->P_Nodes[0] == NULL) {
		//cout << "NO ENCONTRO HIJO IZQUIERDO" << endl;
		p->P_Nodes[0] = new PriorityNode<T>(val, p);
		colita.push(p->P_Nodes[0]);
		PriorityNode<T>* temp = p;
		PriorityNode<T>* temp2 = p->P_Nodes[0];
		while (!o(temp->value, temp->P_Nodes[0]->value)) {
			swap_cuock(temp->value, temp->P_Nodes[0]->value);
			if (temp->P_Nodes[2]) {
				temp = temp->P_Nodes[2];
			}
		}
		return 1;
	}
	else if (p->P_Nodes[1] == NULL) {
		//cout << "NO ENCONTRO HIJO DERECHO" << endl;
		p->P_Nodes[1] = new PriorityNode<T>(val, p);
		colita.push(p->P_Nodes[1]);

		return 1;
	}
	//cout << "AMBOS HIJOS ESTAN OCUPAOS" << endl;
	return 0;
}
template<class T, class Op>
bool PriorityTree<T, Op>::insertar(T val)
{
	if (!Root) {
		Root = new PriorityNode<T>(val);
		colita.push(Root);
		return 1;
	}
	//while (colita.front()->P_Nodes[0] && colita.front()->P_Nodes[1]) {
	if (colita.front()->P_Nodes[0] && colita.front()->P_Nodes[1]) {
		colita.pop();
		//cout << "H:" << colita.front()->value << endl;
	}
	PriorityNode<T>* f = colita.front();
	insertar_node(f, val);
	return 1;
}
template<class T, class Op>
void PriorityTree<T, Op>::PrintPerLevel() {
	queue<PriorityNode<T>*> s;
	if (!Root) { return; }
	s.push(Root);
	int altu_espacio = ((get_altura(Root) + 1) * 2) - 1;
	int altu = get_altura(Root);
	while (!s.empty()) {
		PriorityNode<T>* Haruka = s.front();
		int altu_now = get_altura(Haruka);
		if (altu != get_altura(Haruka)) {
			for (int i = 0; i < altu_espacio; i++) {
				cout << " ";
			}
			cout << endl;
			for (int i = 0; i < altu_now + 1; i++) {
				cout << " ";
			}
			altu_espacio = ((altu + 1) * 2) - 1;
			altu = altu_now;
		}
		else {
			for (int i = 0; i < altu_espacio; i++) {
				cout << " ";
			}
		}
		cout << Haruka->value;
		s.pop();
		if (Haruka->P_Nodes[0]) {
			s.push(Haruka->P_Nodes[0]);
		}
		if (Haruka->P_Nodes[1]) {
			s.push(Haruka->P_Nodes[1]);
		}
	}
}
template<class T, class Op>
int PriorityTree<T, Op>::get_altura(PriorityNode<T>* p)
{
	if (p == NULL) {
		return -1;
	}
	int mayor;
	if (get_altura(p->P_Nodes[0]) > get_altura(p->P_Nodes[1])) {
		mayor = get_altura(p->P_Nodes[0]);
	}
	else {
		mayor = get_altura(p->P_Nodes[1]);
	}
	return 1 + mayor;
}
template<class T, class Op>
void PriorityTree<T, Op>::PrintRight(PriorityNode<T>* p, int cont)
{
	if (!p) {
		return;
	}
	else {
		PrintRight(p->P_Nodes[1], cont + 1);
		for (int i = 0; i < cont; i++) {
			cout << "   ";
		}
		cout << p->value << endl;
		PrintRight(p->P_Nodes[0], cont + 1);
	}
}
template<class T, class Op>
void PriorityTree<T, Op>::resize(unsigned int new_size)
{
	PriorityCap = new_size;
	T* del = data;
	data = new T[new_size];
	int temp;
	if (PriorityCount < new_size) {
		temp = PriorityCount;
	}
	else {
		temp = new_size;
	}
	for (int i = 1; i <= temp; i++) {
		data[i] = del[i];
	}
	if (del) {
		delete[] del;
	}
}
template<class T, class Op>
bool PriorityTree<T, Op>::is_empty()
{
	return PriorityCount == 0;
}
template<class T, class Op>
unsigned int PriorityTree<T, Op>::size()
{
	return PriorityCount;
}
template<class T, class Op>
unsigned int PriorityTree<T, Op>::capacity()
{
	return PriorityCap;
}
template<class T, class Op>
void PriorityTree<T, Op>::recalculate(int iter)
{
	int i = iter;
	while (i != 1 && data[i] > data[i / 2]) {
		swap_cuock(data[i], data[i / 2]);
		//swap(data[i], data[i / 2]);
		i /= 2;
	}
}
template<class T, class Op>
bool PriorityTree<T, Op>::Push(const T& p)
{
	if (PriorityCount + 1 >= PriorityCap) {
		resize(2 * PriorityCap);
	}
	PriorityCount++;
	PriorityLast++;
	data[PriorityLast] = p;
	recalculate(PriorityLast);
	return 1;
}
template<class T, class Op>
bool PriorityTree<T, Op>::Extract_Max()
{
	if (is_empty()) {
		cout << "I WANNA BE LIKE YOU" << endl;
		return 1;
	}
	PriorityCount--;
	data[1] = data[PriorityLast];
	PriorityLast--;

	int i = 1;
	int left, right;
	while (i < PriorityLast) {
		left = 2 * i;
		right = 2 * i + 1;
		if (data[left] > data[right] && (left <= PriorityLast)) {
			swap_cuock(data[i], data[left]);
			i = left;
		}
		else if (right <= PriorityLast) {
			swap_cuock(data[i], data[right]);
			i = right;
		}
		else break;
	}
	return 1;
}
template<class T, class Op>
void PriorityTree<T, Op>::print()
{
	int aux_X = 0;
	int aux_Y = 0;

	int lvl = 0;
	int i = 1;
	int lvl_pow = PriorityLast;
	int m_height = 0;
	while (!(lvl_pow && (!(lvl_pow & (lvl_pow - 1)))))
	{
		lvl_pow++;
	}

	lvl_pow = log(lvl_pow) / log(2) - 1;

	int aux_XX = 0;
	string str = to_string(data[PriorityLast]);
	int len_str = str.length();
	while (i <= PriorityLast)
	{
		aux_X = 2 * pow(2, lvl_pow);
		aux_XX = 2 * pow(2, lvl_pow + 1);
		for (int j = 0; i <= PriorityLast && j < pow(2, lvl); j++)
		{
			gotoxy(aux_X, aux_Y);
			cout << "|" << data[i] << "|";
			if(j!=0)
				cout << "" << "   " << "";
			aux_X += aux_XX + 1;
			i++;
		}
		lvl_pow--;
		aux_Y++;
		lvl++;
	}
	cout << endl;

}
template<class T, class Op>
void HeapSort(PriorityTree<T, Op>* arb)
{
	for (int i = arb->PriorityCount; i > 0; i--) {
		arb->Extract_Max();
	}
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
void printTree(PriorityNode<T>* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr)
		return;

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->P_Nodes[0], trunk, true);

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
	cout << root->value << endl;

	if (prev)
		prev->str = prev_str;
	trunk->str = "   |";

	printTree(root->P_Nodes[1], trunk, false);
}
void menu()
{
	int opcion, dato;
	PriorityTree<int, Mayor<int>> arbolito(1);
	do {
		cout << "\t         MENU   \n";
		cout << "1. Insertar elementos en el arbol\n";
		cout << "2. Mostrar el arbol\n";
		cout << "3. Eliminar un Nodo de la Lista\n";
		cout << "5. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
			cout << "Ingresa un numero: " << endl;
			cin >> dato;
			arbolito.Push(dato);
			cout << "\n";
			system("pause");
			break;
		case 2:  
			system("cls");
			arbolito.Extract_Max();
			arbolito.print();
			cout << "\n";
			system("pause");
			break;
		
		case 3: cout << "Ingrese el elemento que desea eliminar: ";
			//cin >> dato;
			//borrar(lista, dato);
			//cout << "\n";
			//system("pause");

		}
		system("cls");
	} while (opcion != 5);
}
//template<class T, class Op>
int main()
{
	menu();
	
	

}


