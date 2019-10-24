#include <iostream> 
#include <queue> 
using namespace std;


void displaypq(priority_queue <int, vector<int>, greater<int>> pq)
//void displaypq(priority_queue <int> pq)
{
	priority_queue <int, vector<int>, greater<int>> pqueue = pq;
	//priority_queue <int> pqueue = pq;
	while (!pqueue.empty())
	{
		cout << '\t' << pqueue.top();
		pqueue.pop();
	}
	cout << '\n';
}

int main()
{
	priority_queue <int, vector<int>, greater<int>> pq;
	//priority_queue <int> pq;
	pq.push(9);
	pq.push(7);
	pq.push(5);
	pq.push(3);
	pq.push(1);

	cout << "tamaño: " << pq.size();
	cout << "\ncabeza del arbol: " << pq.top();
	cout << "\nelemnto de prioridad : ";
	displaypq(pq);

	//cout << "\nPriority queue, after pq.pop() operation : ";
	//pq.pop();
	//displaypq(pq);

	return 0;
}