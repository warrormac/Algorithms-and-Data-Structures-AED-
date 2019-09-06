#include <iostream>
using namespace std;

int main()
{
	int b[3][4][2];
	int*** x;
	x = new int** [3];
	for (int i = 0; i < 3; i++)
	{
		x[i] = new int* [4];
		for (int j = 0; j < 4; j++)
		{
			x[i][j] = new int[2];
		}
	}
}
