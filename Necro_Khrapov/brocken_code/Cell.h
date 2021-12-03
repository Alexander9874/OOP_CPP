#ifndef CELL_HEADER
#define CELL_HEADER

#include "enums.h"
#include "exceptions.h"

class Cell
{
	private:
		cell_states cell_state;
	public:
		explicit Cell(cell_states state = WALL) :
		cell_state(state) {};

		virtual ~Cell() = default;

		inline cell_states get_cell_state() const noexcept
		{
			return cell_state;
		};

		inline void set_cell_state(const cell_states state)
		{
			if(state < 0 || state > ESSENCE) throw Exception("unavailable_value");
			cell_state = state;
		};
};

class Ladder : public Cell
{
	private:
		size_t offset;
	public:
		explicit Ladder(size_t c) :
		Cell(LADDER), offset(c) {};
		
		~Ladder() = default;

		inline size_t get_offset() const noexcept
		{
			return offset;
		};
		
		inline void set_offset(const size_t state) noexcept
		{
			offset = state;
		};
};

#endif