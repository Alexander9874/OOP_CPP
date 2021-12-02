#include "ALL_IN_ONE.h"

Dungeon * Creature::dungeon = nullptr;

void User::correct()
{
	while(experience >= next_level_experience)
	{
		++skill_point;
		++level;
		if(max_mana < 10) ++max_mana;
		if(get_max_health() < 100) set_max_health(get_max_health() + 10);
		if(get_damage() < 20) set_damage(get_damage() + 2);
		next_level_experience <<= 1;
	}
}

inline void User::set_mana(const int state)
{
	if(state < 0 || state > max_mana) throw Exception("unavailable_value");
	mana = state;
}

void User::set_experience(const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	experience = state;
	correct();
}

inline void User::set_skill_point(const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	skill_point = state;
}

void User::set_skill_power(const skills skill, const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	skill_table[skill] = state;
}

void User::collect_essence()
{
	if(dungeon->get_cell_state(get_position()) != ESSENCE) throw Exception("wrong_type");
	int chance = std::rand() % 10;	//if 0 nothing received
	if(chance > 0 && chance < 4)
	{
		mana_exchange(1);
	}
	if(chance > 3 && chance < 7)
	{
		receive_health(3);
	}
	if(chance > 6 && chance < 10)
	{
		receive_experience(5);
	}
	dungeon->cell_remove(get_position());
}

void User::mana_exchange(const int state)
{
	int num = mana + state;
	if(num < 0) throw Exception("not_enough_mana");
	if(num > max_mana) num = max_mana;
	mana = num;
}

void User::receive_experience(const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	experience += state;
	if(experience >= next_level_experience) correct();
}

void User::receive_health(const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	int num = get_health() + state;
	if(num > get_max_health()) num = get_max_health();
	set_health(num);
}

void User::skill_increase(const skills skill_name)
{
	if(skill_point <= 0) throw Exception("not_enough_skill_point");
	if(skill_table[skill_name] >= 5) throw Exception("already_max_state");
	++skill_table[skill_name];
	--skill_point;
}

void User::wither(Creature * target)
{
	if(skill_table[WITHER] == 0) throw Exception("skill_not_available");
	if(!target->is_alive()) throw Exception("target_is_not_alive");
	Alive_Creature * target_alive = dynamic_cast<Alive_Creature *>(target);
	if(target_alive == nullptr) throw Exception("nullptr_object");
	if(target_alive->is_still_alive()) throw Exception("target_is_still_alive");
	mana_exchange(-skill_table[WITHER]);
	int chance = std::rand() % 10;	//if 0 nothing received
	if(chance > 0 && chance < 4)
	{
		mana_exchange(skill_table[WITHER] + 2);
	}
	if(chance > 3 && chance < 7)
	{
		receive_health(get_max_health() * skill_table[WITHER] / 15);
	}
	if(chance > 6 && chance < 10)
	{
		receive_experience(skill_table[WITHER] * 5);
	}
	dungeon->creature_remove(target->get_position());
}

void User::curse(Creature * target)
{
	if(skill_table[CURSE] == 0) throw Exception("skill_not_available");
	if(!target->is_alive()) throw Exception("target_is_not_alive");
	Alive_Creature * target_alive = dynamic_cast<Alive_Creature *>(target);
	if(target_alive == nullptr) throw Exception("nullptr_object");
	if(!target_alive->is_still_alive()) throw Exception("target_is_not_still_alive");
	mana_exchange(-1 - skill_table[CURSE] / 3);
	int num5 = std::rand() % 5;
	bool num2 = static_cast<bool>(std::rand() % 10);
	target_alive->add_curse_state(static_cast<curse_states>(num5 * 2 + num2), skill_table[CURSE]);
}

void User::necromancy(Creature * target)
{
	if(skill_table[NECROMANCY] == 0) throw Exception("skill_not_available");
	if(!target->is_alive()) throw Exception("target_is_not_alive");
	Alive_Creature * target_alive = dynamic_cast<Alive_Creature *>(target);
	if(target_alive == nullptr) throw Exception("nullptr_object");
	if(target_alive->is_still_alive()) throw Exception("target_is_still_alive");
	mana_exchange(-skill_table[NECROMANCY] - 1);
	Dead_Creature * target_dead = new Dead_Creature(* target_alive);
	dungeon->emplace_creature(target_alive->get_position(), static_cast<Creature *>(target_dead));
}

void User::morphism(Creature * target)
{
	if(skill_table[MORPHISM] == 0) throw Exception("skill_not_available");
	if(target->is_alive()) throw Exception("target_is_alive");
	Dead_Creature * target_dead = dynamic_cast<Dead_Creature *>(target);
	if(target_dead == nullptr) throw Exception("nullptr_object");
	mana_exchange(-skill_table[MORPHISM] - 1);
	if(target_dead->get_fraction() == get_fraction())
	{
		if(!target_dead->dead_state_increase())
		{
			mana_exchange(skill_table[MORPHISM] + 1);
			throw Exception("already_max_state");
		}
	}
	else
	{
		if(!target_dead->dead_state_decrease())
		{
			mana_exchange(skill_table[MORPHISM] + 1);
			throw Exception("already_min_state");
		}
	}
}

bool User::receive_damage(const int magnitude, const int probability)
{
	if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
	if(std::rand() % 100 < probability)
	{
		int health_tmp = get_health() - magnitude;	
		if(health_tmp <= 0)
		{
			set_health(0);
			throw Game_Over();
		}
		set_health(health_tmp);
	}
	return false;
}

void User::to_damage(Creature * target) const
{
	if(this == target) throw Exception("self_harm");
	if(get_fraction() == target->get_fraction()) throw Exception("frendly_fire");
	if(!target->receive_damage(get_damage(), get_damage_probability()))
	{
        dungeon->creature_remove(target->get_position());
        delete target;
	}
}

void User::turn()
{
    //
}

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

inline Creature * Dungeon::get_creature(const std::pair<int, int> position)
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

inline void Dead_Creature::set_dead_state(const dead_states state)
{
    if(state < 0 || state > VAMPIRE) throw Exception("unavailable_value");
    dead_state = state;
}

bool Dead_Creature::dead_state_increase()
{
    if(dead_state == VAMPIRE) return false;
    ++dead_state;
    /*
    int tmp = dead_state;
    ++tmp;
    dead_state = static_cast<dead_states>(tmp);
    */
    return true;
}

bool Dead_Creature::dead_state_decrease()
{
    if(dead_state == GHOST) return false;
    --dead_state;
    /*
    int tmp = dead_state;
    --tmp;
    dead_state = static_cast<dead_states>(tmp);
    */
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
    }
    return false;
}

inline void Creature::lava_damage()
{
	if(dungeon->get_cell_state(get_position()) == LAVA) receive_damage(30, 100);
}

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

inline void Creature::set_creature_state(const creature_states state)
{
	if(state < 0 || state > GOLEM) throw Exception("unavailable_value");
	creature_state = state;
}

inline void Creature::set_max_health(const int state)
{
	if(state <= 0) throw Exception("unavailable_value");
	max_health = state;
}

inline void Creature::set_health(const int state)
{
	if(state < 0 || state > max_health) throw Exception("unavailable_value");
	health = state;
}

inline void Creature::set_fraction_state(const fraction_states state)
{
	if(state < 0 || state > 1) throw Exception("unavailable_value");
	fraction = state;
}

inline void Creature::set_damage(const int state)
{
	if(state <= 0) Exception("unavailable_value");
	damage = state;
}

inline void Creature::set_damage_probability(const int state)
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

std::vector<std::pair<int, int>> Creature::Lee(const std::pair<int, int> position, const int range, const fraction_states _fraction, const search_state search) const
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
            still_alive = false;
            return false;
        }
        set_health(health_tmp);
    }
    return false;
}

#ifdef ALL_IN_ONE_TRUE

#include "Summoner.h"
#include "Golem.h"

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

void Summoner_Alive::turn()
{
    auto steps = Lee(get_position(), 8, !get_fraction(), ALL);
			if(steps.empty()) return;			// steps.size == 0
			auto step = steps.back();			// step = steps.at(step.size)
			
			turn_execute(step);
            summon();
}

////    yes, i know...

void Summoner_Dead::turn()
{
    auto steps = Lee(get_position(), 8, !get_fraction(), ALL);
			if(steps.empty()) return;			// steps.size == 0
			auto step = steps.back();			// step = steps.at(step.size)
			
			turn_execute(step);
            summon();
}

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

#endif