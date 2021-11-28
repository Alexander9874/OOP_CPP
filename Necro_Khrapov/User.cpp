#include "User.h"

void User::correct()
{
	while(experience >= next_level_experience)
	{
		++skill_point;
		++level;
		if(max_mana < 10) ++max_mana;
		if(get_max_health() < 100) set_max_health(get_max_health() + 10);
		if(get_damage() < 20) set_damage(get_damage() + 2);
		next_level_experience << 1;
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

inline void User::set_skill_power(const skills skill, const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	skill_table[skill] = state;
}

void User::mana_exchange(const int state = 0)
{
	int num = mana + state;
	if(num < 0) throw Exception("not_enough_mana");
	if(num > max_mana) num = max_mana;
	mana = num;
}

void User::receive_experience(const int state = 0)
{
	if(state < 0) throw Exception("unavailable_value");
	experience += state;
	if(experience >= next_level_experience) correct();
}

void User::receive_health(const int state = 0)
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

	// delete target from vector in dangeon
}

void User::curse(Creature * target)
{
	if(skill_table[CURSE] == 0) throw Exception("skill_not_available");
	//if(distznce > some_value) throw too_far_away();
	if(!target->is_alive()) throw Exception("target_is_not_alive");
	Alive_Creature * target_alive = dynamic_cast<Alive_Creature *>(target);
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
	if(target_alive->is_still_alive()) throw Exception("target_is_still_alive");
	mana_exchange(-skill_table[NECROMANCY] - 1);
	// vector<Creature> [target_alive->get_position] = Dead_Creatures(* target_alive);
}

void User::morphism(Creature * target)
{
	if(skill_table[MORPHISM] == 0) throw Exception("skill_not_available");
	//if(distznce > some_value) throw too_far_away();
	if(target->is_alive()) throw Exception("target_is_alive");
	Dead_Creature * target_dead = static_cast<Dead_Creature *>(target);
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

void User::receive_damage(const int magnitude, const int probability)
{
	if(magnitude < 0) throw Exception("unavailable_value"); 
	if(probability > 100 || probability < 0) throw Exception("unavailable_value");
	if(std::rand() % 100 < probability)
	{
		int health_tmp = get_health() - magnitude;	
		if(health_tmp <= 0)
		{
			set_health(0);
			return;
		}
		set_health(health_tmp);
	}
}

void User::to_damage(Creature & target) const
{
	if(this == & target) throw Exception("self_harm");
	if(get_fraction() == target.get_fraction()) throw Exception("frendly_fire");
	target.receive_damage(get_damage(), get_damage_probability());
}