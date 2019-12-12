#include <iostream>

using namespace std;


const int ALPHABET = 26;


struct Node
{
	struct Node* children[ALPHABET];

	bool endword;
};


struct Node* getnode()
{
	struct Node* ptr = new Node;
	ptr->endword = false;

	for (int i = 0; i < ALPHABET; i++)
		ptr->children[i] = nullptr;

	return ptr;
}


void insert(struct Node* root, string key)
{
	struct Node* crawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!crawl->children[index])
			crawl->children[index] = getnode();

		crawl = crawl->children[index];
	}

	crawl->endword = true;
}

bool search(Node* root, string key)
{
	struct Node* crawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!crawl->children[index])
			crawl->children[index] = getnode();

		crawl = crawl->children[index];


	}

	return (crawl != NULL && crawl->endword);
}


int main()
{
	string words[] = { "hola","chau","que","como","porque","ah" };
	int size = sizeof(words) / sizeof(words[0]);

	struct Node* root =getnode();

	for (int i = 0; i < size; i++)
		insert(root, words[i]);


	search(root, "hola")?cout<<"si esta":cout<<"no esta";
}