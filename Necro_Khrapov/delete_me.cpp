#include <iostream> 

#include "template_matrix.h"

int main()
{
	Matrix<int> matrix(4, 5);

	for(int i = 0; i < matrix.get_rows(); i++)
	{
		for(int j = 0; j < matrix.get_cols(); j++)
		{
			matrix[std::pair<int, int>(i, j)] = 1;
		}
	}

	std::vector<int> data = matrix.get_data();
	for(auto x : data)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl;
	
	matrix.add_row();

	data = matrix.get_data();
	for(auto x : data)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl;


	for(int i = 0; i < matrix.get_rows(); i++)
	{
		for(int j = 0; j < matrix.get_cols(); j++)
		{
			matrix[std::pair<int, int>(i, j)] = 1;
		}
	}

	data = matrix.get_data();
	for(auto x : data)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl;

	matrix.add_col();



	data = matrix.get_data();
	for(auto x : data)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl;


	for(int i = 0; i < matrix.get_rows(); i++)
	{
		for(int j = 0; j < matrix.get_cols(); j++)
		{
			matrix[std::pair<int, int>(i, j)] = 1;
		}
	}

	data = matrix.get_data();
	for(auto x : data)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl;

	matrix[std::pair<int, int>(3, 3)] = 3;
	matrix[std::pair<int, int>(4, 4)] = 4;

	data = matrix.get_data();
	for(auto x : data)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl;

	matrix.swap(std::pair<int, int>(3, 3), std::pair<int, int>(4, 4));

	data = matrix.get_data();
	for(auto x : data)
	{
		std::cout << x << ' ';
	}
	std::cout << std::endl << std::endl;

	Iterator<int> it;
	for(it = matrix.begin(); it != matrix.end(); ++it)
	{
		*it *= 2;
		std::cout << *it << ' ';
	}
	std::cout << std::endl;

	std::cout << *(matrix.find(std::pair<int, int>(3, 3))) << std::endl;

	Matrix<int>::const_iterator new_it;

	for(new_it = matrix.cbegin(); new_it != matrix.cend(); ++new_it)
	{
		std::cout << * new_it << ' ';
	}
	std::cout << std::endl;

	return 0;
}
