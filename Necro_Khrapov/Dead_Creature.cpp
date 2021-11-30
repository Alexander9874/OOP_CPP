//#include "Dead_Creature.h"

#include "include.h"

inline void Dead_Creature::set_dead_state(const dead_states state)
{
    if(state < 0 || state > (int)"some_value_TBD") throw Exception("unavailable_value");
    dead_state = state;
}

bool Dead_Creature::dead_state_increase()
{
    if(dead_state == GHOUL) return false;
    int tmp = dead_state;
    ++tmp;
    dead_state = static_cast<dead_states>(tmp);
    return true;
}

bool Dead_Creature::dead_state_decrease()
{
    if(dead_state == GHOST) return false;
    int tmp = dead_state;
    --tmp;
    dead_state = static_cast<dead_states>(tmp);
    return true;
}

void Dead_Creature::to_damage(Creature * target) const
{
    if(this == target) throw Exception("self_harm");
    if(get_fraction() == target->get_fraction()) throw Exception("frendly_fire");
    if(target->receive_damage(get_damage() * (1 + dead_state / 10), get_damage_probability()))
    {
        dungeon->creature_remove(target->get_position());
        delete target;
    }
}

bool Dead_Creature::receive_damage(const int magnitude, const int probability)
{
    if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
    if(std::rand() % 100 < probability)
	{
		int health_tmp = get_health() - magnitude * (1 - dead_state / 10);
		if(health_tmp < 0)
        {
            set_health(0);
            return true;
        }
        set_health(health_tmp);
        return false;
    }
}