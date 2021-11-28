#include "include.h"

inline void Summoner::set_summon_probability(const int state)
{
    if(state < 0 || state > 100) throw Exception("unavailable_value");
    summon_probability = state;
}

void Summoner_Alive::summon()
{

}

void Summoner_Dead::summon()
{
    
}