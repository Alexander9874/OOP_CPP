#ifndef DANGEON_HEADER
#define DANGEON_HEADER

#include "include.h"

//#include "template_matrix.h" //???

class Dangeon
{
	private:
		std::map<std::pair<int, int>, Cell *> cells;
		std::map<std::pair<int, int>, Creature *> creatures;
		User * user;
		int level;
		int layer;
	public:
		void load_layer(const size_t offset = 0);
		void load_map(const char * map_name);
		
		void set_cell(std::pair<int, int> position, const cell_states cell);
		void set_cell(Cell & cell, const cell_states state);
		void set_ladder(Ladder & cell, const ladder_states state, const size_t offset);
		void set_ladder(const std::pair<int, int> position, ladder_states state, size_t offset);
		void set_door(const std::pair<int, int> position);
		void set_door(const Cell & door);
};

#endif