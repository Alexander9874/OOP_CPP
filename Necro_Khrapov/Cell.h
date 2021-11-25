#ifndef CELL_HEADER
#define CELL_HEADER

#include "include.h"

class Cell
{
	private:
		cell_states cell_state;
	public:
		Cell(cell_states state) : cell_state(state) {};
		cell_states get_cell_state() const noexcept {return cell_state;};
		void set_cell_state(const cell_states state) noexcept {cell_state = state;};
};

class Ladder : public Cell
{
	private:
		ladder_states ladder_state;
		size_t offset;
	public:
		Ladder(ladder_states b, size_t c) : Cell(LADDER), ladder_state(b), offset(c) {};
		ladder_states get_ladder_state() const noexcept {return ladder_state;};
		size_t get_offset() const noexcept {return offset;};
		
		void set_ladder_state(const ladder_states state) noexcept {ladder_state = state;};
		void set_offset(const size_t state) noexcept {offset = state;};
};

#endif