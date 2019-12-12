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
template<class T>
int maxDepth(Node<T>* node)
{
	if (node == NULL)
		return 0;
	else
	{
		/* compute the depth of each subtree */
		int lDepth = maxDepth(node->N_nodes[0]);
		int rDepth = maxDepth(node->N_nodes[1]);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

template<class T>
void printLeafNodes(Node<T>* root, int &cont)
{
	if (!root)
		return;
	if (root->N_nodes[0])
	{
		//cont++;
		printLeafNodes(root->N_nodes[0],cont);
		
	}
	if (root->N_nodes[1])
	{
		//cont++;
		printLeafNodes(root->N_nodes[1],cont);
		
	}
	if (!root->N_nodes[0] && !root->N_nodes[1])
	{
		cout << root->n_x << " , ";
		cont++;
		return;
	}
}
/*template<class T>
int getLeafCount(Node<T>* node)
{
	if (node == NULL)
		return 0;
	if (node->N_nodes[0] == NULL && node->N_nodes[1] == NULL)
		return 1;
	else
		return getLeafCount(node->N_nodes[0]) +
		getLeafCount(node->N_nodes[1]);
}*/

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


void showTrunks(Trunk* p)
{
	if (p == nullptr)
		return;

	showTrunks(p->prev);

	cout << p->str;
}


template <class T>
void printTree(Node<T>* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr)
		return;
	string color;
	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);


	printTree(root->N_nodes[1], trunk, true);

	if (!prev)
		;// trunk->str = "---";
	else if (isLeft)
	{
		//prev_str = "   |";
		trunk->str = " .---";

	}
	else
	{
		trunk->str = " `---";
		//prev_str = "   |";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << root->n_x << color << endl;
	trunk->str = " ";
	if (prev)
		prev->str = prev_str;
	trunk->str = "   ";


	printTree(root->N_nodes[0], trunk, false);
}


int main()
{
	int cont=0;

	Tree<int, Less<int> > Ent;
	Ent.Insert(8);
	Ent.Insert(3);
	Ent.Insert(10);
	Ent.Insert(1);
	Ent.Insert(14);
	Ent.Insert(6);
	Ent.Insert(5);
	Ent.Insert(100);
	Ent.Insert(35);
	Ent.Insert(15);
	Ent.Insert(25);
	Ent.Insert(45);
	Ent.Insert(55);
	Ent.Insert(65);

	printTree<int>(Ent.n_root, nullptr, false);
	system("pause");

	cout << "Height of tree is " << maxDepth(Ent.n_root);
	cout << endl;
	cout << "las Hojas son: ";
	//cout<<getLeafCount(Ent.n_root);
	printLeafNodes(Ent.n_root,cont);
	cout << "\nla catidad de hojas son: " << cont;
	return 0;

}