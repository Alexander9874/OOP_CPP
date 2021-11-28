#include "include.h"

inline void Creature::set_creature_state(const creature_states state)
{
	if(state < 0 || state > (int)"some_value_TBD") throw Exception("unavailable_value");
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

inline void Creature::set_damage_probability(const float state)
{
	if(state < 0.1 || state > 1) throw Exception("unavailable_value");
	damage_probability = round(state * 100) / 100;
}