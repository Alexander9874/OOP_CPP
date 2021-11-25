#include "User.h"

void User::correct_next_level() // change!!!
{
	next_level_experience = (8.52 * exp(0.93 * level));
	max_health = 198 + 109 * level - level * level * 5.87;
	max_mana = 198 + 109 * level - level * level * 5.87; // max == 10
	damage = 9.85 + 5.67 * level - 0.213 * level * level;
	++skill_point;
}

void User::set_max_mana(const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	max_mana = state;
}

void User::set_mana(const int state)
{
	if(state < 0 || state > max_mana) throw Exception("unavailable_value");
	mana = state;
}

void User::set_level(const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	level = state;
	correct_next_level();
}

void User::set_skill_point(const int state)
{
	if(state < 0) throw Exception("unavailable_value");
	skill_point = state;
}

void User::set_skill_power(const skills skill, const int state)
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
	if(experience >= next_level_experience) correct_next_level();
}

void User::receive_health(const int state = 0)
{
	if(state < 0) throw Exception("unavailable_value");
	int num = health + state;
	if(num > max_health) num = max_health;
	health = num;
}

void User::wither(Creature * target)
{
	if(skill_table[WITHER] == 0) throw Exception("skill_not_available");
	if(!target->is_alive()) throw Exception("target_is_not_alive");
	Alive_Creature * target_alive = static_cast<Alive_Creature *>(target);
	if(target_alive->is_still_alive()) throw Exception("target_is_still_alive");
	mana_exchange(-skill_table[WITHER]);
	int chance = std::rand() % 3;
	if(chance == 0)
	{
		mana_exchange(skill_table[WITHER] + 2);
	}
	if(chance == 1)
	{
		receive_health(max_health / 10);
	}
	else
	{
		receive_experience(next_level_experience / 20);
	}

	// delete target from vector in dangeon
}

void User::curse(Creature * target)
{
	if(skill_table[CURSE] == 0) throw Exception("skill_not_available");
	//if(distznce > some_value) throw too_far_away();
	if(!target->is_alive()) throw Exception("target_is_not_alive");
	Alive_Creature * target_alive = static_cast<Alive_Creature *>(target);
	if(!target_alive->is_still_alive()) throw Exception("target_is_not_still_alive");
	mana_exchange(-1 - skill_table[CURSE] / 3);
	int num5 = std::rand() % 5;
	bool num2 = static_cast<bool>(std::rand() % 5);
	target_alive->add_curse_state(static_cast<curse_states>(num5 + num2), skill_table[CURSE]);
}

void User::necromancy(Creature * target)
{
	if(skill_table[NECROMANCY] == 0) throw Exception("skill_not_available");
	if(!target->is_alive()) throw Exception("target_is_not_alive");
	Alive_Creature * target_alive = static_cast<Alive_Creature *>(target);
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
	if(target_dead->get_fraction() == fraction)
	{
		if(!target_dead->state_increase())
		{
			mana_exchange(skill_table[MORPHISM] + 1);
			throw Exception("already_max_state");
		}
	}
	else
	{
		if(!target_dead->state_decrease())
		{
			mana_exchange(skill_table[MORPHISM] + 1);
			throw Exception("already_min_state");
		}
	}
}

void User::skill_increase(const skills skill_name)
{
	if(skill_point == 0) throw Exception("not_enough_skill_point");
	++skill_table[skill_name];
	--skill_point;
}