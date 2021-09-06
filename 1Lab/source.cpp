#include "header.h"

namespace NameSpaceLab1
{
	void CreateMatrix(Matrix &matrix)
	{
		matrix.items = new double*[matrix.cols];
		for(int i = 0; i < matrix.cols; i++)
		{
			matrix.items[i] = new double[matrix.rows];
		}
	}
	
	int FillMatrix(Matrix &matrix)
	{
		cout << "\nEnter your MATRIX. ROW by ROW.\n" << endl;
		for(int i = 0; i < matrix.rows; i++)
		{
			bool ERR = true;
			while(ERR)
			{
				ERR = false;
				for(int j = 0; j < matrix.cols; j++)
				{
					try
					{
						getSomething(matrix.items[j][i]);
					}
					catch(int x)
					{
						if(x)
						{
							return -1;
						}
						else
						{
							ERR = true;
							cout << "Repeat ROW." << endl;
							break;
						}
					}
				}
			}
		}
		cout << endl;
		return 0;
	}
	
	int DialogCreate(Matrix &matrix)
	{
		string msg = "";
		cout << "\nEnter number of ROWS and COLUMNS.\n >> ";
		while(1)
		{
			cout << msg;
			msg = "Try again!\n";
			
			try
			{
				getSomething(matrix.rows);
				getSomething(matrix.cols);
			}
			catch(int x)
			{
				if(x)
				{
					return -1;
				}
				else
				{
					continue;
				}
			}
			if(matrix.rows <= 0 || matrix.cols <= 0)
			{
				cout << "Incorrect size of matrix." << endl;
				continue;
			}
			try
			{
			CreateMatrix(matrix);
			}
			catch(bad_alloc &x)
			{
				cout << x.what() << endl;
				return -1;
			}
			break;
		}
		return 0;
	}
	
	void ModifyMatrix(Matrix &matrix)
	{
		for(int i = 0; i < matrix.rows; i++)
		{
			swap(matrix.items[i % matrix.cols][i], 	matrix.items[abs(matrix.cols - i - 1) % matrix.cols][i]);
		}
	}
	
	void PrintMatrix(Matrix matrix)
	{
		for(int i = 0; i < matrix.rows; i++)
		{
			for(int j = 0; j < matrix.cols; j++)
			{
				cout << matrix.items[j][i] << '\t';
			}
			cout << endl << endl;
		}
	}
	
	void DeleteMatrix(Matrix matrix)
	{
		for(int i = 0; i < matrix.cols; i++)
		{
			delete [] matrix.items[i];
		}
		delete [] matrix.items;
	}
	
	vector<int>* MakeVector(Matrix matrix)
	{
		vector<int>* vect;
		try
		{
			vect = new vector<int>;
		}
		catch(bad_alloc &x)
		{
			cout << x.what() << endl;
			return nullptr;
		}
		for(int i = 0; i < matrix.rows; i++)
		{
			vect->push_back (INT_MIN);
			for(int j = 0; j < matrix.cols; j++)
			{
				int count = 1;
				for(int k = j + 1; k < matrix.cols; k++)
				{
					if(matrix.items[j][i] == matrix.items[k][i])
					{
						count++;
					}
				}
				if((*vect)[i] < count)
				{
					(*vect)[i] = count;
				}
			}
		}
		return vect;
	}
	
	void PrintVector(vector<int> vect)
	{
		cout << "Vector :\n" << endl;
		for(int i : vect)
		{
			cout << i << ' ';
		}
		cout << '\n' << endl;
	}
}	
