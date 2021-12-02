#include "Summoner.h"

inline void Summoner::set_summon_probability(const int state)
{
    if(state < 0 || state > 100) throw Exception("unavailable_value");
    summon_probability = state;
}

void Summoner_Alive::summon()
{
    if(get_summon_probability() >= std::rand() % 100) return;
    std::pair<int, int> position(get_position());
    for(int i = -1; i < 2; ++i)
    {
        for(int j = -1; j < 2; ++j)
        {
            if(!j && !i) continue;
            if(dungeon->get_cell_state(std::pair<int, int>(position.first + i, position.second + j)) == FLOOR && !dungeon->is_creature(std::pair<int, int>(position.first + i, position.second + j)))
            {
                creature_states creature_state = static_cast<creature_states>(std::rand() % SUMMONER);
                Alive_Creature * alive_creature = new Alive_Creature(creature_state);
                dungeon->emplace_creature(std::pair<int, int>(position.first + i, position.second + j), alive_creature);
                return;
            }
        }
    }
}

void Summoner_Dead::summon()
{
    if(get_summon_probability() >= std::rand() % 100) return;
    std::pair<int, int> position(get_position());
    for(int i = -1; i < 2; ++i)
    {
        for(int j = -1; j < 2; ++j)
        {
            if(!j && !i) continue;
            if(dungeon->get_cell_state(std::pair<int, int>(position.first + i, position.second + j)) == FLOOR && !dungeon->is_creature(std::pair<int, int>(position.first + i, position.second + j)))
            {
                creature_states creature_state = static_cast<creature_states>(std::rand() % SUMMONER);
                Dead_Creature * dead_creature = new Dead_Creature(creature_state, get_dead_state());
                dungeon->emplace_creature(std::pair<int, int>(position.first + i, position.second + j), dead_creature);
                return;
            }
        }
    }   
}