#include "Dungeon_and_Creature.h"

Dungeon * Creature::dungeon = nullptr;

void Creature::set_position(const std::pair<int, int> state)
{
	std::pair<int, int> limits(dungeon->get_limits());
	if(state.first < 0 || state.second < 0 || state.first > limits.first || state.second > limits.second) throw Exception("out_of_range");
	cell_states cell = dungeon->get_cell_state(state);
	if(dungeon->is_creature(state) || cell == WALL || cell == DOOR_CLOSED || cell == LADDER) throw Exception("place_is_taken");
	if(dungeon->is_creature(position))
	{
		if(dungeon->get_creature(position) == this)
		{
			dungeon->creature_extract(position);
		}
		else
		{
			throw Exception("wrong_statment");
		}
	}
	dungeon->emplace_creature(state, this);
	position = state;
}

void Creature::set_creature_state(const creature_states state)
{
	if(state < 0 || state > GOLEM) throw Exception("unavailable_value");
	creature_state = state;
}

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

void Creature::set_fraction_state(const fraction_states state)
{
	if(state < 0 || state > 1) throw Exception("unavailable_value");
	fraction = state;
}

void Creature::set_damage(const int state)
{
	if(state <= 0) Exception("unavailable_value");
	damage = state;
}

void Creature::set_damage_probability(const int state)
{
	if(state < 0 || state > 100) throw Exception("unavailable_value");
	damage_probability = state;
}

void Creature::set_dungeon(Dungeon * state)
{
	if(dungeon) throw Exception("static_member_is_alredy_set");
	dungeon = state;
}

void Creature::turn_execute(const std::pair<int, int> direction)
{
	auto dispalcesment = direction - position;
	if(abs(dispalcesment.first) + abs(dispalcesment.second) > 1) throw Exception("too_far_away");
	if(dungeon->is_creature(direction))
	{
		to_damage(dungeon->get_creature(direction));
		return;
	}
	cell_states cell = dungeon->get_cell_state(direction);
	if(cell == WALL || cell == DOOR_CLOSED || cell == LADDER) throw Exception("wrong_directio");
	set_position(direction);
}
//// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
std::vector<std::pair<int, int>> Creature::Lee(const int range, const alive_states search, const fraction_states _fraction) const
{
/*	std::pair<bool, bool> compare;
	if(search == ALL)
	{
		compare = std::pair<bool, bool>(true, false);
	}
	else if(search == ALIVE)
	{
		compare = std::pair<bool, bool>(true, true);
	}
	else if(search == DEAD)
	{
		compare = std::pair<bool, bool>(false, false);
	}
	else
	{
		throw Exception("unavailable_value");
	}
*/
	std::map<std::pair<int, int>, int> labels;
	std::set<std::pair<int, int>> next;
	std::vector<std::pair<int, int>> steps;
	int iteration = 0;
	labels.emplace(position, iteration++);

	std::pair<int, int> x(1, 0), y(0, 1);

	next.emplace(position + x);
	next.emplace(position - x);
	next.emplace(position + y);
	next.emplace(position - y);
	cell_states cell;
	while(iteration < range)
	{
		std::set<std::pair<int, int>> tmp;
		for(auto i : next)
		{
			if(labels.contains(i)) continue;
			if(dungeon->is_creature(i))
			{
				Creature * creature = dungeon->get_creature(i);
				if(creature->get_fraction() == _fraction && ((search == ALL && creature->is_alive() != ZERO_HEALTH) || search == creature->is_alive()))
				//if(creature->get_fraction() == _fraction && (compare.first == creature->is_alive() || compare.second == creature->is_alive()))
				{
					steps.push_back(i);
					break;
				}
				continue;
			}
			cell = dungeon->get_cell_state(i);
			if(cell == FLOOR || cell == LAVA || cell == DOOR_OPENED)
			{
					tmp.emplace(i + x);
					tmp.emplace(i - x);
					tmp.emplace(i + y);
					tmp.emplace(i - y);
					labels.try_emplace(i, iteration);
			}
		}
		if(steps.size()) break;
		++iteration;
		next = tmp;
	}
	if(!steps.size()) return steps;
	for(--iteration ; iteration > 0; --iteration)
	{
		std::pair<int, int> tmp = steps.back();
		if(labels.contains(tmp + x) && labels.at(tmp + x) == iteration) 
		{
			steps.push_back(tmp + x);
			continue;
		}
		if(labels.contains(tmp - x) && labels.at(tmp - x) == iteration) 
		{
			steps.push_back(tmp - x);
			continue;
		}
		if(labels.contains(tmp + y) && labels.at(tmp + y) == iteration) 
		{
			steps.push_back(tmp + y);
			continue;
		}
		if(labels.contains(tmp - y) && labels.at(tmp - y) == iteration) 
		{
			steps.push_back(tmp - y);
			continue;
		}
		throw Exception("Lee_algorithm_failed");
	}
	return steps;
}

Dungeon::~Dungeon()
{
	for(auto i : creatures)
		{
			delete i.second;
		}
}

Creature * Dungeon::get_configuration(const creature_states state) const
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

void Dungeon::set_cell(std::pair<int, int> position, cell_states state)
{
    if(position.first < 0 || position.second < 0 || position.first > limits.first || position.second > limits.second) throw Exception("out_of_range");
    cells.emplace(position, Cell(state));
}

void Dungeon::set_ladder(std::pair<int, int> position, const size_t offset)
{
    if(!cells.contains(position)) throw Exception("does_not_exist");
    Cell cell = cells[position];
    if(cell.get_cell_state() != LADDER) throw Exception("wrong_type");
    Ladder * cell_ladder = static_cast<Ladder *>(& cell);                   // ???
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

void Dungeon::set_limits(const std::pair<int, int> position)
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

cell_states Dungeon::get_cell_state(std::pair<int, int> position) const noexcept
{
    if(!cells.contains(position)) return FLOOR;
    return cells.at(position).get_cell_state();
}
/*
bool Dungeon::is_creature(const std::pair<int, int> position) const
{
    if(position.first < 0 || position.second < 0 || position.first > limits.first || position.second > limits.second) throw Exception("out_of_range");
    return creatures.contains(position);
}
*/
Creature * Dungeon::get_creature(const std::pair<int, int> position)
{
    if(!creatures.contains(position)) throw Exception("does_not_exist");
    return creatures.at(position);
}

std::pair<std::pair<int, int>, Creature *> Dungeon::creature_extract(std::pair<int, int> position)
{
    if(!creatures.contains(position)) throw Exception("does_not_exist");
    std::pair<std::pair<int, int>, Creature *> tmp(position, creatures[position]);
    creatures.erase(position);
    return tmp;
}

void Dungeon::cell_remove(std::pair<int, int> position)
{
    if(!cells.erase(position)) throw Exception("does_not_exist");
}

void Dungeon::creature_remove(std::pair<int, int> position)
{
    if(!creatures.contains(position)) throw Exception("does_not_exist");
    delete creatures[position];
    creatures.erase(position);

    //if(!creatures.erase(position)) throw Exception("does_not_exist");
}

void Dungeon::try_emplace_cell(std::pair<int, int> position, cell_states state)
{
    if(position.first < 0 || position.second < 0 || position.first > limits.first || position.second > limits.second) throw Exception("out_of_range");
    cells.try_emplace(position, Cell(state));
}

#include <iostream>

void Dungeon::turns()
{
	while(true)
	{
		std::map<std::pair<int, int>, Creature *> tmp = creatures;
		std::map<std::pair<int, int>, Creature *>::iterator it;

		for(it = tmp.begin(); it != tmp.end(); it++)
		{
			it->second->turn();
		}

		tmp = creatures;
		for(it = tmp.begin(); it != tmp.end(); it++)
		{
			auto obj = it->second;
			std::cout << obj->get_creature_state() << '(' << obj->get_position().first << ',' << obj->get_position().second << ')' << obj->get_health() << ' ' << obj->is_alive() << std::endl;
		}
	}
}