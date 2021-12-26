#include "Alive_Creature.h"

void Alive_Creature::add_curse_state(const curse_states state, const int magnitude)
{
    if(magnitude < 1) throw Exception("unavailable_value");
    curse_state.push_back(std::pair<curse_states, int>(state, magnitude));
}

void Alive_Creature::to_damage(Creature * target) const
{
    if(this == target) throw Exception("self_argument");
	if(get_fraction() == target->get_fraction()) throw Exception("frendly_fire");
    double koeff_d = 1, koeff_p = 1;
    int damage_p = get_damage_probability();
    for(auto i : curse_state)
    {
        if(i.first == WEAKNESS)
        {
            koeff_d /= pow(1.2, i.second);
        }
        else if(i.first == INACCURACY)
        {
            koeff_p = (koeff_p * damage_p - (100 - damage_p) * i.second / 5 * damage_p * koeff_p) / damage_p;
        }
        else if(i.first == STRENGTH)
        {
            koeff_d *= pow(1.2, i.second);
        }
        else if(i.first == ACCURACY)
        {
            // K(n+1) = (K(n) * P + (1-P) * P * K(n) * strength_of_effect) / P
            koeff_p = (koeff_p * damage_p + (100 - damage_p) * i.second / 5 * damage_p * koeff_p) / damage_p;
        }
    }
    if(target->receive_damage(get_damage() * koeff_d, damage_p * koeff_p))
    {
        dungeon->creature_remove(target->get_position());
        delete target;
    }
}

bool Alive_Creature::receive_damage(const int magnitude, const int probability)
{
    if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
	int damage_p = get_damage_probability();
    double koeff_m = 1, koeff_p = 1;

    for(auto i : curse_state)
    {
        if(i.first == CLUMSINESS)
        {
            koeff_p = (koeff_p * damage_p + (100 - damage_p) * i.second / 5 * damage_p * koeff_p) / damage_p;
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
            koeff_p = (koeff_p * damage_p - (100 - damage_p) * i.second / 5 * damage_p * koeff_p) / damage_p;
        }
    }
    if(std::rand() % 100 < probability * koeff_p)
	{
        int health_tmp = get_health() - magnitude * koeff_m;
		if(health_tmp < 0)
        {
            set_health(0);
            set_alive_state(ZERO_HEALTH);
            //alive = ZERO_HEALTH;
            //still_alive = false;
            return false;
        }
        set_health(health_tmp);
    }
    return false;
}