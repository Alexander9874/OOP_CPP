//#include "Dead_Creature.h"

#include "include.h"

bool Dead_Creature::state_increase()
{
    if(dead_state == GHOUL) return false;
    int tmp = dead_state;
    ++tmp;
    dead_state = static_cast<dead_states>(tmp);
    return true;
}

bool Dead_Creature::state_decrease()
{
    if(dead_state == GHOST) return false;
    int tmp = dead_state;
    --tmp;
    dead_state = static_cast<dead_states>(tmp);
    return true;
}

void Dead_Creature::to_damage(Creature & target) const
{
    if(this == & target) throw Exception("self_harm");
    if(fraction == target.get_fraction()) throw Exception("frendly_fire");
    target.receive_damage(damage * (1 + dead_state / 10), damage_probability);
}

void Dead_Creature::receive_damagee(const int magnitude, const int probability)
{
    if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
    if(std::rand() % 100 < probability)
	{
		health -= magnitude * (1 - dead_state / 10);
		if(health < 0)
        {
            health = 0;
        }
    }
}