#include "Golem.h"

inline void Golem::set_recieve_damage_probability(const int state)
{
    if(state > 100 || state < 0) throw Exception("unavailable_value");
    receive_damage_probability = state;
}

inline void Golem::set_golem_state(const golem_states state)
{
    if(state < 0 || state > 2) throw Exception("unavailable_value");
    golem_state = state;
}

bool Golem::receive_damage(const int magnitude, const int probability)
{
    if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
    if(std::rand() % 10000 < probability * receive_damage_probability)
	{
        int health_tmp = get_health() - magnitude;
		if(health_tmp < 0)
        {
            set_health(0);
            return true;
        }
        set_health(health_tmp);
    }
    return false;
}

void Golem::to_damage(Creature * target) const
{
    if(this == target) throw Exception("self_harm");
    if(get_fraction() == target->get_fraction()) throw Exception("frendly_fire");
    if(!target->receive_damage(get_damage() * (1 + golem_state / 5), get_damage_probability()))
    {
        dungeon->creature_remove(target->get_position());
        delete target;
    }
}