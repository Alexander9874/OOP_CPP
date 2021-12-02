#include "ALL_IN_ONE.h"

inline Creature * Dungeon::get_configuration(const creature_states state) const
{
    if(state < 0 || state > GOLEM) throw Exception("does_not_exist");
    return creature_configuration.at(state);
}
/*
void Dungeon::load_layer(const size_t offset = 0)
{

}

void Dungeon::load_map(const char * map_name)
{

}
*/
inline void Dungeon::set_cell(std::pair<int, int> position, cell_states state)
{
    if(position.first < 0 || position.second < 0 || position.first > limits.first || position.second > limits.second) throw Exception("out_of_range");
    cells.emplace(position, Cell(state));
}

void Dungeon::set_ladder(std::pair<int, int> position, const size_t offset)
{
    if(!cells.contains(position)) throw Exception("does_not_exist");
    Cell cell = cells[position];
    if(cell.get_cell_state() != LADDER) throw Exception("wrong_type");
    Ladder * cell_ladder = static_cast<Ladder *>(& cell);  // dynamic - ??    ///////????????
    cell_ladder->set_offset(offset);
}

void Dungeon::set_door(const std::pair<int, int> position)
{
    if(!cells.contains(position)) throw Exception("does_not_exist");
    Cell cell = cells[position];
    cell_states state = cell.get_cell_state(); 
    if(state != DOOR_CLOSED || state != DOOR_OPENED) throw Exception("wrong_type");
    if(state == DOOR_OPENED) cell.set_cell_state(DOOR_CLOSED);
    else cell.set_cell_state(DOOR_OPENED);
}

inline void Dungeon::set_limits(const std::pair<int, int> position)
{
    if(position.first <= 0 || position.second <= 0) throw Exception("out_of_range");
    limits = position;
}

void Dungeon::emplace_creature(std::pair<int, int> position, Creature * creature)
{
    if(creatures.contains(position)) creature_remove(position);
    if(position.first < 0 || position.second < 0 || position.first > limits.first || position.second > limits.second) throw Exception("out_of_range");
    creatures.emplace(position, creature);
}

inline cell_states Dungeon::get_cell_state(std::pair<int, int> position) const noexcept
{
    if(!cells.contains(position)) return FLOOR;
    return cells.at(position).get_cell_state();
}

inline bool Dungeon::is_creature(const std::pair<int, int> position) const
{
    if(position.first < 0 || position.second < 0 || position.first > limits.first || position.second > limits.second) throw Exception("out_of_range");
    return creatures.contains(position);
}

inline void Dungeon::cell_remove(std::pair<int, int> position)
{
    if(!cells.erase(position)) throw Exception("does_not_exist");
}

inline void Dungeon::creature_remove(std::pair<int, int> position)
{
    if(!creatures.contains(position)) throw Exception("does_not_exist");
    delete creatures[position]; //auto ptr ???
    creatures.erase(position);

    //if(!creatures.erase(position)) throw Exception("does_not_exist");
}

inline void Dungeon::try_emplace_cell(std::pair<int, int> position, cell_states state)
{
    if(position.first < 0 || position.second < 0 || position.first > limits.first || position.second > limits.second) throw Exception("out_of_range");
    cells.try_emplace(position, Cell(state));
}