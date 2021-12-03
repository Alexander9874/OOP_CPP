#include "Creature.h"

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
	dungeon->emplace_creature(position, this);
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

std::vector<std::pair<int, int>> Creature::Lee(const int range, const search_state search, const fraction_states _fraction) const
{
	std::pair<bool, bool> compare;
	if(search == ALL)
	{
		compare = std::pair<bool, bool>(true, false);
	}
	if(search == ALIVE)
	{
		compare = std::pair<bool, bool>(true, true);
	}
	if(search == DEAD)
	{
		compare = std::pair<bool, bool>(false, false);
	}
	else
	{
		throw Exception("unavailable_value");
	}

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
				if(creature->get_fraction() == _fraction && (compare.first == creature->is_alive() || compare.second == creature->is_alive()))
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
