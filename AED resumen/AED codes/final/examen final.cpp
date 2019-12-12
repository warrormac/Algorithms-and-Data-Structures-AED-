#include <iostream>
#include <stdio.h>
#include <stack>
#include <queue>

#include<map>

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
int maxDepth(Node<T>* node)// la profundidad
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
void printLeafNodes(Node<T>* root, int& cont)// las hojas
{
	if (!root)
		return;
	if (root->N_nodes[0])
	{
		//cont++;
		printLeafNodes(root->N_nodes[0], cont);

	}
	if (root->N_nodes[1])
	{
		//cont++;
		printLeafNodes(root->N_nodes[1], cont);

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





template<class T> // nodos internos
int countNonleaf(Node<T>* root, int& cont)
{
	if (root == NULL || (root->N_nodes[0] == NULL && root->N_nodes[1] == NULL))
		return 0;
	cont++;
	
	return 1 + countNonleaf(root->N_nodes[0], cont) + countNonleaf(root->N_nodes[1], cont);
}






template<class T>
void findProductSum(Node<T>* root, int& prod, int& sum)//suma de nodo internos
{
	if (root == NULL || (root->N_nodes[0] == NULL
		&& root->N_nodes[1] == NULL))
		return;


	if (root->N_nodes[0] != NULL || root->N_nodes[1] != NULL)
	{
		prod *= root->n_x;
		sum += root->n_x;
	}

	findProductSum(root->N_nodes[0], prod, sum);
	findProductSum(root->N_nodes[1], prod, sum);
}







template<class T>
void mirror(struct Node<T>* node) // espejo
{
	if (node == NULL)
		return;

	else
	{
		Node<T>* temp;
		mirror(node->N_nodes[0]);

		mirror(node->N_nodes[1]);


		temp = node->N_nodes[0];
		node->N_nodes[0] = node->N_nodes[1];
		node->N_nodes[1] = temp;
	}
}





template<class T>
int isBSTUtil(Node<T>* node, int min, int max)//b search
{
	if (node == NULL)
		return 1;

	if (node->n_x < min || node->n_x > max)
		return 0;

	return
		isBSTUtil(node->N_nodes[0], min, node->n_x - 1) &&
		isBSTUtil(node->N_nodes[1], node->n_x + 1, max);
}
template<class T>
int isBST(Node<T>* node)//b search
{
	return(isBSTUtil(node, INT_MIN, INT_MAX));
}


void printArray(int ints[], int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		cout << ints[i] << " ";
	}
	cout << endl;
}



template<class T>
void printPathsRecur(Node<T>* node, int path[], int pathLen)//pritn route 
{
	if (node == NULL)
		return;

	path[pathLen] = node->n_x;
	pathLen++;

	if (node->N_nodes[0] == NULL && node->N_nodes[1] == NULL)
	{
		printArray(path, pathLen);
	}
	else
	{
		printPathsRecur(node->N_nodes[0], path, pathLen);
		printPathsRecur(node->N_nodes[1], path, pathLen);
	}
}
template<class T>
void printPaths(Node<T>* node)//pritn route 
{
	int path[1000];
	printPathsRecur(node, path, 0);
}



template<class T>
void fillMap(Node<T>* root, int d, int l, map<int, pair<int, int>>& m) { //top view
	if (root == NULL) return;

	if (m.count(d) == 0) {
		m[d] = make_pair(root->n_x, l);
	}
	else if (m[d].second > l) {
		m[d] = make_pair(root->n_x, l);
	}

	fillMap(root->N_nodes[0], d - 1, l + 1, m);
	fillMap(root->N_nodes[1], d + 1, l + 1, m);
}

template<class T>
void topView(Node<T>* root) {//top view

	map<int, pair<int, int>> m;

	fillMap(root, 0, 0, m);

	for (auto it = m.begin(); it != m.end(); it++) {
		cout << it->second.first << " ";
	}
}


template<class T>
void rightViewUtil(Node<T>* root, int level, int* max_level) // print right view
{
	if (root == NULL) return;

	if (*max_level < level)
	{
		cout << root->n_x << "\t";
		*max_level = level;
	}

	rightViewUtil(root->N_nodes[1], level + 1, max_level);
	rightViewUtil(root->N_nodes[0], level + 1, max_level);
}

template<class T>
void rightView(Node<T>* root)//print right view
{
	int max_level = 0;
	rightViewUtil(root, 1, &max_level);
}

template<class T>
void leftViewUtil(Node<T>* root, int level, int* max_level)
{
	if (root == NULL)
		return;

	if (*max_level < level) {
		cout << root->n_x << "\t";
		*max_level = level;
	}

	leftViewUtil(root->N_nodes[0], level + 1, max_level);
	leftViewUtil(root->N_nodes[1], level + 1, max_level);
}

template<class T>
void leftView(Node<T>* root)
{
	int max_level = 0;
	leftViewUtil(root, 1, &max_level);
}




template <class T>
int addBT(Node<T>* root)
{
	if (root == NULL)
		return 0;
	return (root->n_x + addBT(root->N_nodes[0]) + addBT(root->N_nodes[1]));
}


template <class T>
void averageOfLevels(Node<T>* root)
{
	vector<float> res;

	// Traversing level by level 
	queue<Node<T>*> q;
	q.push(root);

	while (!q.empty()) {

		// Compute sum of nodes and 
		// count of nodes in current 
		// level. 
		int sum = 0, count = 0;
		queue<Node<T>*> temp;
		while (!q.empty()) {
			Node<T>* n = q.front();
			q.pop();
			sum += n->n_x;
			count++;
			if (n->N_nodes[0] != NULL)
				temp.push(n->N_nodes[0]);
			if (n->N_nodes[1] != NULL)
				temp.push(n->N_nodes[1]);
		}
		q = temp;
		cout << (sum * 1.0 / count) << "   ";
	}
}





template <class T>
void printOddNodes(Node<T>* root, bool isOdd = false) // chage to true if odd   keep false for even
{
	// If empty tree 
	if (root == NULL)
		return;

	// If current node is of odd level 
	if (isOdd)
		cout << root->n_x << " ";

	// Recur for children with isOdd 
	// switched. 
	printOddNodes(root->N_nodes[0], !isOdd);
	printOddNodes(root->N_nodes[1], !isOdd);
}





template <class T>
void leafSum(Node<T>* root, int* sum) {
	if (!root)
		return;

	// add root data to sum if  
	// root is a leaf node 
	if (!root->N_nodes[0] && !root->N_nodes[1])
		* sum += root->n_x;

	// propagate recursively in left 
	// and right subtree 
	leafSum(root->N_nodes[0], sum);
	leafSum(root->N_nodes[1], sum);
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
	int cont = 0, conter = 0,tempo=0;

	Tree<int, Less<int> > Ent;
	Ent.Insert(8);
	Ent.Insert(3);
	Ent.Insert(10);
	Ent.Insert(1);
	Ent.Insert(14);
	Ent.Insert(6);
	Ent.Insert(4);
	Ent.Insert(7);
	Ent.Insert(13);
	Ent.Insert(15);

	printTree<int>(Ent.n_root, nullptr, false);
	system("pause");



	//funcion find un elemnto
	Node<int>** p;
	cout << Ent.Find(5, p);






	cout << endl;
	cout << endl;


	//funcion tamño del arbol
	cout << "Height of tree is " << maxDepth(Ent.n_root);
	cout << endl;




	//funcion las hojas
	cout << "las Hojas son: ";




	//cout<<getLeafCount(Ent.n_root);
	printLeafNodes(Ent.n_root, cont);
	cout << "\nla catidad de hojas son: " << cont;
	cout << endl;


	//sumatoria de las hojas
	int sumar = 0;
	leafSum(Ent.n_root, &sumar);
	cout <<"la suma de las hojas es: "<< sumar << endl;
	cout << endl;




	//funcion vista arriba
	cout << "Following are nodes in top view of Binary Tree\n";
	topView(Ent.n_root);
	cout << endl;



	//funcion lazo izqu
	cout << "laso izquierdo del arbol\n";
	leftView(Ent.n_root);
	cout << endl;
	cout << endl;




	//funcion lazo der
	cout << "laso derecho del arbol\n";
	rightView(Ent.n_root);
	cout << endl;
	cout << endl;






	//funcion BTS
	cout << "es BTS?\n";
	if (isBST(Ent.n_root))
		cout << "si es BST";
	else
		cout << "no es BST";


	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;




	//funcion reflejo
	cout << "arbol reflejado\n";
	mirror(Ent.n_root);
	printTree<int>(Ent.n_root, nullptr, false);
	cout << endl;
	cout << endl;





	//funcion nodos internos
	cout << "la cantidad de nodos internos son: " << countNonleaf(Ent.n_root, conter);
	cout << endl;



	//funcion suma de nodos internos
		
	int prod = 1;
	int suma = 0;

	findProductSum(Ent.n_root, prod, suma); 
	cout << "Product de los nodos internos = " << prod << " , Sum nodos internos = " << suma;
	cout << endl;
	cout << endl;
	cout << endl;




	//funcion promedio
	cont = cont + conter;
	float sum = addBT(Ent.n_root);
	cout << "suma of all the elements is: " << sum << endl;
	cout << "el promedio es: " << sum / cont;



	cout << endl;
	cout << endl;


	//funcion de promedio por nivel
	averageOfLevels(Ent.n_root);

	cout << endl;
	cout << endl;

	//funcion recorridos
	cout << "camino de raiz a hoja\n";
	printPaths(Ent.n_root);


	cout << endl;
	cout << endl;

	//funcion  nodos en nivel impar/par
	printOddNodes(Ent.n_root);


	cout << endl;
	cout << endl;

	return 0;

}



/*1. find
  2. tamaño del arbol
  3. las hojas
  4. suma de las hojas
  5. vista arriba
  6. lado izq
  7. lado der
  8. BTS
  9. reflejo
  10. nodos internos
  11.suma y multi de nodos internos
  12.sumatoria de todos los nodos
  13.promedio general
  14.promedio por nivel
  15.recorridos
  16.nivel impar/par
  
  */




/*/
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
}

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
}*/