#include "header.h" 

int main()
{
	Matrix matrix;
	
	if(DialogCreate(matrix))
	{
		return -1;
	}
	if(FillMatrix(matrix))
	{
		DeleteMatrix(matrix);
		return -1;
	}
	cout << "Original MATRIX:" << endl << endl;
	PrintMatrix(matrix);
	ModifyMatrix(matrix);
	cout << "Modified MATRIX:" << endl << endl;
	PrintMatrix(matrix);
	vector<int>* vect = MakeVector(matrix); 
	if(!vect)
	{
		DeleteMatrix(matrix);
		return -1;
	}
	PrintVector(*vect);
	delete vect;
	DeleteMatrix(matrix);
	return 0;
}
