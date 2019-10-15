#include <iostream>
#include <stdio.h>
#include <stack>

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
	bool Find(T x, Node<T>**& p);
	bool Insert(T x);
	bool Delete(T x);
	Node<T>** rep(T x, Node<T>** p);
	void inOrder(struct Node<T>* root);
	void postOrder(struct Node<T>* root);
	void preorder(struct Node<T>* root);


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
void Tree<T, O>::inOrder(struct Node<T>* root)
{
	stack<Node<T>*> s;
	Node<T>* curr = root;

	while (curr != NULL || s.empty() == false)
	{
		while (curr != NULL)
		{
			s.push(curr);
			curr = curr->N_nodes[0];
		}
		curr = s.top();
		s.pop();
		cout << curr->n_x << " ";
		curr = curr->N_nodes[1];

	}
}



/*template <class T, class O>
void Tree<T, O>::inOrder(struct Node<T>* root)
{
	stack<Node <T>*>s;
	Node<T>* curr = root;
	while (curr != NULL || s.empty() == false)
	{
		while (curr != NULL)
		{
			s.push(curr);
			curr = curr->N_nodes[0];
		}
		curr = s.top();
		s.pop();
		cout << curr->n_x;
		curr = curr->N_nodes[1];
	}

}
template<class T, class O>
void Tree<T, O>::postOrder(Node<T>* root)
{
	if (root == NULL)
		return;

	stack<Node<T>*> s1, s2;

	s1.push(root);
	Node<T>* node;

	while (!s1.empty()) {

		node = s1.top();
		s1.pop();
		s2.push(node);

		if (node->N_nodes[0])
			s1.push(node->N_nodes[0]);
		if (node->N_nodes[1])
			s1.push(node->N_nodes[1]);
	}

	while (!s2.empty()) {
		node = s2.top();
		s2.pop();
		cout << node->n_x << " ";
	}
}
template <class T, class O>
void Tree<T, O>::postOrder(Node<T>* root)
{
	if (root == NULL)return;
	stack<Node<T>*>s1, s2;
	s1.push(root);
	Node<T>* nodo;

	while (!s1.empty())
	{
		nodo = s1.top();
		s1.pop();
		s2.push(nodo);
		if (nodo->N_nodes[0])
			s1.push(nodo->N_nodes[0]);
		if (nodo->N_nodes[1])
			s2.push(nodo->N_nodes[1]);
	}
	while (!s2.empty())
	{
		nodo = s2.top();
		s2.pop();
		cout << nodo->n_x;
	}
}*/

template <class T, class O>
void Tree<T, O>::preorder(struct Node<T>* root)
{
	stack <Node<T>*>s;
	Node<T>* curr;

	curr = root;
	while (curr != NULL || s.empty() == false)
	{
		
		while (curr != NULL)
		{
			cout << curr->n_x;
			s.push(curr);
			curr = curr->N_nodes[0];
		}
		curr = s.top();
		s.pop();
		curr = curr->N_nodes[1];
	}
}



int main()
{
	Tree<int, Less<int> > Ent;


	cout << "-----BINARY TREE-----" << endl;
	cout << "\n";

	struct Node<int>* root = new Node<int>(1);
	root->N_nodes[0] = new Node<int>(2);
	root->N_nodes[1] = new Node<int>(3);
	root->N_nodes[0]->N_nodes[0] = new Node<int>(4);
	root->N_nodes[0]->N_nodes[1] = new Node<int>(5);

	Ent.preorder(root);
	return 0;

}
