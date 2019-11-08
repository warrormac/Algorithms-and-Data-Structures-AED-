#include<iostream>
#include<stdlib.h>
#include <queue>
using namespace std;


// An AVL tree node

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
	node->height = 1; // new node is initially

	return(node);
}


// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
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


// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
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


// Get Balance factor of node N

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

	else // Equal keys are not allowed in BST
		return node;

	node->height = 1 + max(height(node->left),
		height(node->right));


	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rightRotate(node);
	// Right Right Case

	if (balance < -1 && key > node->right->key)
		return leftRotate(node);
	// Left Right Case

	if (balance > 1 && key > node->left->key)

	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	// Right Left Case

	if (balance < -1 && key < node->right->key)

	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	/* return the (unchanged) node pointer */
	return node;
}
void printLevelOrder(Node* root)
{
	// Base Case
	if (root == NULL) return;

	// Create an empty queue for level order tarversal
	queue<Node*> q;

	// Enqueue Root and initialize height
	q.push(root);

	while (q.empty() == false)
	{

		int nodeCount = q.size();


		while (nodeCount > 0)
		{
			Node* node = q.front();
			cout << "\t" << node->key << " ";
			q.pop();
			if (node->left != NULL)
				q.push(node->left);
			if (node->right != NULL)
				q.push(node->right);
			nodeCount--;
		}
		cout << endl;
	}
}
void preOrder(Node* root)
{

	if (root != NULL)

	{

		printLevelOrder(root);
		//preOrder(root->left);
		//preOrder(root->right);

	}
}


// Driver Code

int main()
{

	Node* root = NULL;



	/* Constructing tree given in

	the above figure */

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);
	root = insert(root, 26);
	root = insert(root, 90);
	root = insert(root, 1);


	/* The constructed AVL Tree would be

				30

			/ \

			20 40

			/ \ \

		10 25 50

	*/

	cout << "Preorder traversal of the "
		"constructed AVL tree is \n";
	preOrder(root);
	return 0;
}
