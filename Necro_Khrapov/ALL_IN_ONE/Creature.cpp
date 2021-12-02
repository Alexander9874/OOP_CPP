#include "ALL_IN_ONE.h"

Dungeon * Creature::dungeon = nullptr;

inline void Creature::lava_damage()
{
	if(dungeon->get_cell_state(get_position()) == LAVA) receive_damage(30, 100);
}

inline void Creature::set_position(const std::pair<int, int> state)
{
	std::pair<int, int> limits(dungeon->get_limits());
	if(state.first < 0 || state.second < 0 || state.first > limits.first || state.second > limits.second) throw Exception("out_of_range");
	position = state; 
}

inline void Creature::set_creature_state(const creature_states state)
{
	if(state < 0 || state > GOLEM) throw Exception("unavailable_value");
	creature_state = state;
}

inline void Creature::set_max_health(const int state)
{
	if(state <= 0) throw Exception("unavailable_value");
	max_health = state;
}

inline void Creature::set_health(const int state)
{
	if(state < 0 || state > max_health) throw Exception("unavailable_value");
	health = state;
}

inline void Creature::set_fraction_state(const fraction_states state)
{
	if(state < 0 || state > 1) throw Exception("unavailable_value");
	fraction = state;
}

inline void Creature::set_damage(const int state)
{
	if(state <= 0) Exception("unavailable_value");
	damage = state;
}

inline void Creature::set_damage_probability(const int state)
{
	if(state < 0.1 || state > 1) throw Exception("unavailable_value");
	damage_probability = round(state * 100) / 100;
}

inline void Creature::set_dungeon(Dungeon * state)
{
	if(dungeon) throw Exception("static_member_is_alredy_setted");
	dungeon = state;
}