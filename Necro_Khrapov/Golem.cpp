#include "include.h"

void Golem::set_recieve_damage_probability(const int state = 70)
{
    if(state > 100 || state < 0) throw Exception("unavailable_value");
    receive_damage_probability = state;
}

void Golem::receive_damage(const int magnitude, const int probability)
{
    if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
    if(std::rand() % 10000 < probability * receive_damage_probability)
	{
		health -= magnitude;
		if(health < 0)
        {
            health = 0;
        }
    }
}

void Golem::to_damage(Creature & target) const
{
    if(this == & target) throw Exception("self_harm");
    if(fraction == target.get_fraction()) throw Exception("frendly_fire");
    target.receive_damage(damage * (1 + golem_state / 5), damage_probability);
}