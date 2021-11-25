//#include "Alive_Creature.h"

#include "include.h"

void Alive_Creature::add_curse_state(const curse_states state, const int magnitude)
{
    if(magnitude < 1) throw Exception("unavailable_value");
    curse_state.push_back(std::pair<curse_states, int>(state, magnitude));
}

void Alive_Creature::to_damage(Creature & target) const
{
    if(this == & target) throw Exception("self_argument");
	if(fraction == target.get_fraction()) throw Exception("frendly_fire");
    double koeff_d = 1, koeff_p = 1;
    for(auto i : curse_state)
    {
        if(i.first == WEAKNESS)
        {
            koeff_d /= pow(1.2, i.second);
        }
        else if(i.first == INACCURACY)
        {
            koeff_p = (koeff_p * damage_probability - (100 - damage_probability) * i.second / 5 * damage_probability * koeff_p) / damage_probability;
        }
        else if(i.first == STRENGTH)
        {
            koeff_d *= pow(1.2, i.second);
        }
        else if(i.first == ACCURACY)
        {
            // K(n+1) = (K(n) * P + (1-P) * P * K(n) * strength_of_effect) / P
            koeff_p = (koeff_p * damage_probability + (100 - damage_probability) * i.second / 5 * damage_probability * koeff_p) / damage_probability;
        }
    }
    target.receive_damage(damage * koeff_d, damage_probability * koeff_p);
}

void Alive_Creature::receive_damage(const int magnitude, const int probability)
{
    if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
	
    double koeff_m = 1, koeff_p = 1;

    for(auto i : curse_state)
    {
        if(i.first == CLUMSINESS)
        {
            koeff_p = (koeff_p * damage_probability + (100 - damage_probability) * i.second / 5 * damage_probability * koeff_p) / damage_probability;
        }
        else if(i.first == MORTIFICATION)
        {
            koeff_m *= pow(1.2, i.second);
        }
        else if(i.first == RESISTANCE)
        {
            koeff_m /= pow(1.2, i.second);
        }
        else if (i.first == DODGE)
        {
            koeff_p = (koeff_p * damage_probability - (100 - damage_probability) * i.second / 5 * damage_probability * koeff_p) / damage_probability;
        }
    }
    if(std::rand() % 100 < probability * koeff_p)
	{
		health -= magnitude * koeff_m;
		if(health < 0)
        {
            health = 0;
            still_alive = false;
        }
    }
}