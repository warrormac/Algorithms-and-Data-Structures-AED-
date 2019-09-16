#include <iostream>
#include <algorithm>   
using namespace std;

int main()
{

	// Get the array 
	int arr[] = { 1, 45, 54, 71, 76, 12 };

	// Find the size of the array 
	int n = sizeof(arr) / sizeof(arr[0]);

	// Print the array 
	cout << "Array: ";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;

	// Sort the array 
	std::sort(arr,arr+n);

	
	cout << "Sorted Array: ";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
	// Sort the array 
	std::sort(arr, arr + n, greater<>());
	cout << "Sorted Array in Descending: ";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;

}