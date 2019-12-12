//Circular Linked List

#include <iostream>
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
	cout << endl;
}

int main(int argc, char* argv[]) {
	CircLL<int> A;
	A.insertar(5);
	A.insertar(7);
	A.insertar(9);
	A.insertar(11);
	A.insertar(4);
	A.insertar(6);
	A.insertar(8);
	A.insertar(7);
	A.insertar(3);
	A.insertar(15);
	A.imprimir();
	A.borrar(3);
	A.imprimir();
	A.borrar(8);
	A.imprimir();
	A.borrar(15);
	A.imprimir();
	A.borrar(11);
	A.imprimir();
	A.insertar(3);
	A.imprimir();
	return 0;
}
