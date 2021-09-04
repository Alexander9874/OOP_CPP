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
//int getNum(T &x)
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
/*
		for(int j = 0; j < matrix.rows; j++)
		{
			matrix.items[i][j] = i + j;
		}
*/
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
				//cout << "EOF occured!" << endl;
				return -1;
			}
			else
			{
				//cout << "Wrong input!" << endl;
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

double* CreateVector(Matrix matrix)
{
	try
	{
		double* vector = new double[matrix.rows];
	}
	catch(bad_alloc x)
	{
		cout << x.what() << endl;
		return nullptr;
	}
	for(int i = 0; i < matrix.rows; i++)
	{
//		vector[i] = CountInRow()
	}
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

for(int i = 0; i < 3; i++)
cout << matrix.items[0][i];

	DeleteMatrix(matrix);

	return 0;
}
