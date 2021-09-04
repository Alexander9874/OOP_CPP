#include <iostream>
using namespace std;

struct Matrix
{
        int raws;
	int cols;
	double** items;
};



void alloc(Matrix &matrix)
{
	matrix.items = new double*[1];
	matrix.items[0] = new double[1];
	matrix.item[0][0] = 9;
}

int main()
{
	Matrix matrix;
	alloc(matrix);
	cout << matrix.items[0][0] << endl;

	return 0;
}
