#include <iostream> 
#include <queue>
using namespace std;

enum Color { RED, BLACK };

struct Node
{
	int data;
	bool color;
	Node* left, * right, * parent;
	Node(int data)
	{
		this->data = data;
		left = right = parent = NULL;
		this->color = RED;
	}
};


struct Trunk
{
public:
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

void printTree(Node*, Trunk*, bool);
class RBTree
{
private:
	Node* root;
protected:
	void rotateLeft(Node*&, Node*&);
	void rotateRight(Node*&, Node*&);
	void fixViolation(Node*&, Node*&);
public:
	RBTree() { root = NULL; }
	void insert(const int& n);
	void inorder();
	void levelOrder();
};

void inorderHelper(Node* root)
{
	if (root == NULL)
		return;

	inorderHelper(root->left);
	cout << root->data << "  ";
	inorderHelper(root->right);
}

Node* BSTInsert(Node* root, Node* pt)
{
	if (root == NULL)
		return pt;

	if (pt->data < root->data)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->data > root->data)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}
	return root;
}

void levelOrderHelper(Node* root)
{
	if (root == NULL)
		return;

	std::queue<Node*> q;
	q.push(root);

	while (!q.empty())
	{
		Node* temp = q.front();
		cout << temp->data << "  ";
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);

		if (temp->right != NULL)
			q.push(temp->right);
	}
}

void RBTree::rotateLeft(Node*& root, Node*& pt)
{
	Node* pt_right = pt->right;

	pt->right = pt_right->left;

	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_right;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;

	pt_right->left = pt;
	pt->parent = pt_right;
}

void RBTree::rotateRight(Node*& root, Node*& pt)
{
	Node* pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}

void RBTree::fixViolation(Node*& root, Node*& pt)
{
	Node* parent_pt = NULL;
	Node* grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED))
	{

		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		if (parent_pt == grand_parent_pt->left)
		{

			Node* uncle_pt = grand_parent_pt->right;

			if (uncle_pt != NULL && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}

			else
			{
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}

		else
		{
			Node* uncle_pt = grand_parent_pt->left;


			if ((uncle_pt != NULL) && (uncle_pt->color == RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{

				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}

void RBTree::insert(const int& data)
{
	Node* pt = new Node(data);

	root = BSTInsert(root, pt);

	fixViolation(root, pt);
}

void RBTree::inorder() { printTree(root, nullptr, false); }
void RBTree::levelOrder() { levelOrderHelper(root); }

void printTree(Node* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr)
		return;

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->left, trunk, true);

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
	printTree(root->right, trunk, false);
}

int main()
{
	int menu = 0;
	int num;
	RBTree tree;
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
			tree.insert(num);
			tree.inorder();
			system("pause");
		}
		if (menu == 2)
			tree.inorder();
		if (menu == 3)
		{
			;
		}
		
	}
	
	
	



	return 0;
}