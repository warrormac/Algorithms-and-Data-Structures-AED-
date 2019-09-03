#include <iostream>
#include <thread>

using namespace std;

void F1(char c, int n)
{
	for (int i = 0; i < n; i++)
		cout << c;
}


int calculadora(int x, int y)
{
	return x + y;
}
void main()
{
	int temp;
	int nt = thread::hardware_concurrency();
	thread t=thread(F1,'c',10);
	temp=calculadora(10, 5);
	cout << temp;
	t.join();
}