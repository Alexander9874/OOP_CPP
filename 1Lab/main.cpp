#include "header.h" 

int main()
{
	Matrix matrix;
	
	if(DialogCreate(matrix) || FillMatrix(matrix))
	{
		return -1;
	}
	cout << "Original MATRIX:" << endl << endl;
	PrintMatrix(matrix);
	ModifyMatrix(matrix);
	cout << "Modified MATRIX:" << endl << endl;
	PrintMatrix(matrix);
	vector<int>* vect = MakeVector(matrix); 
	PrintVector(*vect);
	delete vect;
	DeleteMatrix(matrix);

	return 0;
}
