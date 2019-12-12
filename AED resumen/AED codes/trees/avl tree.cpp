#include<iostream> 
#include <iomanip>
using namespace std;
  
class Node
{
public:
	int key;
	Node* left;
	Node* right;
	int height;
};

int max(int a, int b);

int height(Node* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

Node* newNode(int key)
{
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; 
	return(node);
}
  
Node* rightRotate(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;
 
	x->right = y;
	y->left = T2;
 
	y->height = max(height(y->left),
		height(y->right)) + 1;
	x->height = max(height(x->left),
		height(x->right)) + 1;

	return x;
}

Node* leftRotate(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left),
		height(x->right)) + 1;
	y->height = max(height(y->left),
		height(y->right)) + 1;

	return y;
}

int getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
  
Node* insert(Node* node, int key)
{
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	node->height = 1 + max(height(node->left),
		height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void preOrder(Node* root)
{
	if (root != NULL)
	{
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}
void prints(Node* reference, int identation,int a)
{
	if (!reference)
		return;
	prints(reference->left, identation + 4,1);
	if (identation && a == 1) {
		std::cout << std::setw(identation) << ' ';
		std::cout << "/`" << reference->key << std::endl;
	}
	if (identation && a == 2) {
		std::cout << std::setw(identation) << ' ';
		std::cout << " \." << reference->key << std::endl;
	}
		
	prints(reference->right, identation + 4,2);
	return;
}

int main()
{
	Node* root = NULL;

	root = insert(root, 4);
	root = insert(root, 5);
	root = insert(root, 6);
	root = insert(root, 7);
	root = insert(root, 2);
	root = insert(root, 9);


	root = insert(root, 1);
	root = insert(root, 8);
	root = insert(root, 3);

	prints(root, 0,0);

	return 0;
}