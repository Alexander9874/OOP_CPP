#include <vector>
#include <iostream>
#include <climits>
using namespace std;

struct Matrix
{
	int rows;
	int cols;
	double** items;
};

template <class T>
void getSomething(T &x)
{
	cin >> x;
	if(cin.eof())
	{
		cout << "EOF occured!" << endl;
		throw -1;
	}
	if(cin.fail())
	{
		cout << "Wrong input!" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		throw 0;
	}
}

template <class T>
inline void Swap(T &x, T &y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

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
	cout << "Enter your MATRIX. ROW by ROW.\n" << endl;
	for(int i = 0; i < matrix.rows; i++)
	{
		while(1)
		{
			try
			{
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
							throw 0;
						}
					}
				}
			}
			catch(int x)
			{
				cout << "Repeat ROW." << endl;
				continue;
			}
			break;
		}
	}
	cout << endl;
	return 0;
}

int DialogCreate(Matrix &matrix)
{
	string msg = "";
	cout << "Enter number of ROWS and COLUMNS.\n >> ";
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
		swap(matrix.items[i][i], matrix.items[matrix.cols - i - 1][i]);
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
	cout << endl;
}

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
