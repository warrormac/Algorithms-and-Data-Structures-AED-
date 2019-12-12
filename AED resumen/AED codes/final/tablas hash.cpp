#include <iostream>
#include <list>
using namespace std;


class Hash
{

	int BUCKET; 
	list<int>* lista;
public:
	Hash(int V);

	void ingresar(int);
	void eliminar(int);
	void mostrar();

	int func(int key){
		return (key % BUCKET);
	}
		

};


Hash::Hash(int key)
{
	this->BUCKET = key;
	lista = new list<int>[BUCKET];
 }


void Hash::ingresar(int data )
{
	int index = func(data);
	lista[index].push_back(data);
}


void Hash::eliminar(int data)
{
	int index = func(data);
	list<int>::iterator itr;
	for (itr = lista[index].begin(); itr != lista[index].end(); itr++)
	{
		if (*itr == data)
			break;
	}

	if (itr != lista[index].end())
		lista[index].erase(itr);
}
void Hash::mostrar()
{
	for (int i = 0; i < BUCKET; i++)
	{
		cout << i;
		for (auto x : lista[i])
			cout << "-> " << x;
		cout << endl;
	}
		
}
int main()
{
	int arr[] = { 5,10,3,20,17 };
	int size = sizeof(arr) / sizeof(arr[0]);

	Hash h(7);

	for (int i = 0; i < size; i++)
		h.ingresar(arr[i]);

	h.mostrar();
	system("pause");
	


	h.eliminar(10);
	h.mostrar();
}