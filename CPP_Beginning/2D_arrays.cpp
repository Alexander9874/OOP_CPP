#include <iostream>
using namespace std;

const int num = 100000;

int main()
{
	double** matrix = new double*[num];

	for (int i = 0; i < num; i++)
	{
		matrix[i] = new double[num];
	}
	
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			cout << matrix[j][i] << " ";
		}
		cout << endl;
	}

	return 0;
}
