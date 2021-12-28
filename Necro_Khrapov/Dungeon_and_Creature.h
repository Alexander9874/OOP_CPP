#ifndef DUNGEON_AND_CREATURE_HEADER
#define DUNGEON_AND_CREATURE_HEADER

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iostream>

#include "exceptions.h"
#include "enums.h"
#include "Cell.h"

template <typename X, typename Y>                                                   
inline std::pair<X, Y> operator + (const std::pair<X, Y> & first, const std::pair<X, Y> & second)
{   
    return std::pair<X, Y>(first.first + second.first, first.second + second.second);
}

template <typename X, typename Y>                                                   
inline std::pair<X, Y> operator - (const std::pair<X, Y> & first, const std::pair<X, Y> & second)
{   
    return std::pair<X, Y>(first.first - second.first, first.second - second.second);
}

class User;

class Creature;

class Dungeon
{
	protected:
		std::map<creature_states, Creature *> creature_configuration;

		std::map<std::pair<int, int>, Cell> cells;
		std::map<std::pair<int, int>, Creature *> creatures;
		User * user;
		std::pair<int, int> limits;
		int level;
		int layer;
	public:

		Dungeon()
		{

		}

		~Dungeon();

		//void load_configuration();

		Creature * get_configuration(const creature_states state) const;
/*
		void load_layer(const size_t offset = 0);
		void load_map(const char * map_name);
*/		
		void set_cell(std::pair<int, int> position, const cell_states state);
		void set_ladder(std::pair<int, int> position, const size_t offset);
		void set_door(const std::pair<int, int> position);
		void set_limits(const std::pair<int, int> positioin);

		void emplace_creature(std::pair<int, int> position, Creature * creature);

		cell_states get_cell_state(std::pair<int, int> position) const noexcept;
		inline std::pair<int, int> get_limits() const noexcept
		{
			return limits;
		};
		inline bool is_creature(const std::pair<int, int> position) const noexcept
		{
			return creatures.contains(position);
		}
		Creature * get_creature(const std::pair<int, int> position);
		std::pair<std::pair<int, int>, Creature *> creature_extract(std::pair<int, int> position);

		void cell_remove(std::pair<int, int> position);
		void creature_remove(std::pair<int, int> position);
		void try_emplace_cell(const std::pair<int, int> position, cell_states state);

		void turns();
};

/**
 * @brief класс существ, класс абстрактный.
 * @brief brief description
 *
 */

class Creature
{
	private:
		std::pair<int, int> position; //	(x, y) x: right & left, y: up & down
		creature_states creature_state;
		int max_health;
		int health;
		fraction_states fraction;
		int damage;
		int damage_probability;
		alive_states alive;
	protected:
		static Dungeon * dungeon;
	public:
		explicit Creature(creature_states st, int mh, fraction_states f, int d, int dp, alive_states a) :
		creature_state(st), max_health(mh), health(max_health), fraction(f), damage(d), damage_probability(dp), alive(a)
		{
			if(max_health < 0) throw Exception("unavailable_value");
			if(damage < 0) throw Exception("unavailable_value");
			if(damage_probability < 0 || damage_probability > 100) throw Exception("unavailable_value");
		}

		virtual ~Creature() = default;

		virtual bool receive_damage(const int magnitude, const int probability) = 0;
 		virtual void to_damage(Creature * target) const = 0;
		
		inline bool lava_damage()
		{
			if(dungeon->get_cell_state(get_position()) == LAVA) 
			{
				return receive_damage(30, 100);
			}
			return false;
		};

		inline std::pair<int, int> get_position() const noexcept
		{
			return position;
		};
		inline creature_states get_creature_state() const noexcept
		{
			return creature_state;
		};
		inline int get_max_health() const noexcept
		{
			return max_health;
		};
		inline int get_health() const noexcept
		{
			return health;
		};
		inline fraction_states get_fraction() const noexcept
		{
			return fraction;
		};
		inline int get_damage() const noexcept{
			return damage;
		};
		inline int get_damage_probability() const noexcept
		{
			return damage_probability;
		};
		inline alive_states is_alive() const noexcept
		{
			return alive;
		}
		inline Dungeon * get_dungeon() const noexcept
		{
			return dungeon;
		};

		void set_position(const std::pair<int, int> state);
		void set_creature_state(const creature_states state);
		void set_max_health(const int state);
		void set_health(const int state);
		void set_fraction_state(const fraction_states state);
		void set_damage(const int state);
		void set_damage_probability(const int state);
		void set_alive_state(const alive_states state);
		void set_dungeon(Dungeon * state);

		void turn_execute(const std::pair<int, int> direction);

		std::vector<std::pair<int, int>> Lee(const int range, const alive_states search, const fraction_states _fraction) const;
		virtual bool turn()	//Alive_Creature & Summoner & User edit!
		{
			if(lava_damage()) return true;
			if(get_health() == 0) return true;
			auto steps = Lee(10, ALL, !fraction);
			if(steps.empty()) return false;			// steps.size == 0
			auto step = steps.back();			// step = steps.at(step.size)
std::cout << "DEAD?" << std::endl;			
			turn_execute(step);
			return false;
		}
};

#endif