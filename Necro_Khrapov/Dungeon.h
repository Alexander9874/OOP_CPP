#ifndef DANGEON_HEADER
#define DANGEON_HEADER

#include <map>
#include <utility>

#include "exceptions.h"
#include "Creature.h"
#include "Cell.h"
#include "User.h"
#include "enums.h"

class User;

class Creature;

class Dungeon
{
	private:
		std::map<creature_states, Creature *> creature_configuration;

		std::map<std::pair<int, int>, Cell> cells;	////???????
		std::map<std::pair<int, int>, Creature *> creatures;
		User * user;
		std::pair<int, int> limits;
		int level;
		int layer;
	public:
		inline Creature * get_configuration(const creature_states state) const;
/*
		void load_layer(const size_t offset = 0);
		void load_map(const char * map_name);
*/		
		inline void set_cell(std::pair<int, int> position, const cell_states state);
		void set_ladder(std::pair<int, int> position, const size_t offset);
		void set_door(const std::pair<int, int> position);
		inline void set_limits(const std::pair<int, int> positioin);

		void emplace_creature(std::pair<int, int> position, Creature * creature);

		inline cell_states get_cell_state(std::pair<int, int> position) const noexcept;
		inline std::pair<int, int> get_limits() const noexcept {return limits;};
		inline bool is_creature(const std::pair<int, int> position) const;

		inline void cell_remove(std::pair<int, int> position);
		inline void creature_remove(std::pair<int, int> position);
		inline void try_emplace_cell(const std::pair<int, int> position, cell_states state);
};

#endif