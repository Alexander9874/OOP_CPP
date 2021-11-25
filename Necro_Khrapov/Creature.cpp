//#include "Creature.h"

#include "include.h"

void Creature::set_max_health(const int state)
{
	if(state <= 0) throw Exception("unavailable_value");
	max_health = state;
}

void Creature::set_health(const int state)
{
	if(state < 0 || state > max_health) throw Exception("unavailable_value");
	health = state;
}

void Creature::set_damage(const int state)
{
	if(state <= 0) Exception("unavailable_value");
	damage = state;
}

void Creature::set_damage_probability(const float state)
{
	if(state < 0.1 || state > 1) throw Exception("unavailable_value");
	damage_probability = round(state * 100) / 100;
}