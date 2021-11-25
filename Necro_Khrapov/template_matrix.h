#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include <exception>
#include <vector>

class incorrect_size : public std::exception
{
	virtual const char * what() noexcept
	{
		return "Incorrect size of Matrix.";
	}
};

class incorrect_indexes : public std::exception
{
	virtual const char * what() noexcept
	{
		return "Incorrect index / indexes, no such elment.";
	}
};

template<class T>
class Iterator
{
	private:
		typename std::vector<T>::iterator current; // почему нужен typename
	public:
		Iterator() {};
		Iterator(typename std::vector<T>::iterator it) : current(it) {}; // здесь тоже
		bool operator != (const Iterator & i) const noexcept
		{
			return current != i.current;
		}
		bool operator == (const Iterator & i) const noexcept
		{
			return current == i.current;
		}
		T & operator * () const noexcept
		{
			return * current;
		}
		T * operator -> () const noexcept
		{
			return & (* current);
		}
		Iterator & operator ++ () noexcept
		{
			++current;
			return * this;
		}
		Iterator operator ++ (T) noexcept
		{
			Iterator result(* this);
			++current;
			return result;
		}
		Iterator & operator -- () noexcept
		{
			--current;
			return *this;
		}
		Iterator operator -- (T) noexcept
		{
			Iterator result(* this);
			--current;
			return result;
		}
};

template<class T>
class Matrix
{
	protected:
		std::vector<T> data;
		int rows;
		int cols;
		int size;
	public:
		explicit Matrix(int r, int c) : rows(r), cols(c), size(rows * cols)
		{
			if(r < 0 || c < 0) throw incorrect_size();
			data = std::vector<T>(size); 
		}
		Matrix() : rows(0), cols(0) {};
		~Matrix() = default;
		int get_rows() const noexcept
		{
			return rows;
		}
		int get_cols() const noexcept
		{
			return cols;
		}
		std::vector<T> get_data() const
		{
			return data;
		}
		std::vector<T> get_row(const int row) const 
		{
			if(row > rows || row < 0) throw incorrect_indexes();
			std::vector<T> result(cols);
			int index = cols * row;
			for(int i = 0; i < cols; ++i)
			{
				result[i] = data[index + i];
			}
			return result;
		}
		std::vector<T> get_col(const int col) const
		{
			if(col > cols || col < 0) throw incorrect_indexes();
			std::vector<T> result(rows);
			int index = col;
			for(int i = 0; i < rows; ++i)
			{
				result[i] = data[index];
				index += cols;
			}
			return result;
		}
		T & operator [] (const std::pair<int, int> coord)
		{
			int row = coord.first, col = coord.second;
			if(row > rows || row < 0 || col > cols || col < 0) throw incorrect_indexes();
			return data[row * cols + col];
		}
		void set_size(const int row, const int col)
		{
			if(row < 0 || col < 0) throw incorrect_size();
			rows = row;
			cols = col;
			data = std::vector<T>(rows * cols);
			size = rows * cols;
		}
		void clear()
		{
			data.clear();
			rows = 0;
			cols = 0;
			size = 0;
		}
		void add_row()
		{
			++rows;
			data.resize(rows * cols);
			size += cols;
		}
		void add_col()
		{
			std::vector<T> new_data(rows * (cols + 1));
			for(int i = 0; i < rows; ++i)
			{
				for(int j = 0; j < cols; ++j)
				{
					new_data[j + i * (cols + 1)] = data[j + i * cols];
				}
			}
			data = new_data;
			++cols;
			size += rows;
		}
		void swap(const std::pair<int, int> first, const std::pair<int, int> second)
		{
			if(first.first > rows || first.first < 0 || first.second > cols || first.second < 0 || second.first > rows || second.first < 0 || second.second > cols || second.second < 0) throw incorrect_indexes();
			if(first.first == second.first && first.second == second.second) return;
			T tmp = data[first.second + cols * first.first];
			data[first.second + cols * first.first] = data[second.second + cols * second.first];
			data[second.second + cols * second.first] = tmp;
		}
		typedef Iterator<T> iterator;
		typedef const Iterator<T> const_iterator;	//WRONG
		Iterator<T> begin() noexcept
		{
			return Iterator<T>(data.begin());
		}
		Iterator<T> end() noexcept
		{
			return Iterator<T>(data.end());
		}
		const Iterator<T> cbegin() const noexcept
		{
			return Iterator<T>(data.cbegin());
		}
		const Iterator<T> cend() const noexcept
		{
			return Iterator<T>(data.ceng());
		}
		Iterator<T> find(const std::pair<int ,int> coords) noexcept
		{
			return Iterator<T>(data.begin() + coords.first * cols + coords.second);
		}
};

#endif
