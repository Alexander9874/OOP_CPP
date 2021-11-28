#include "Necro_Khrapov.h"
/*
void Creature::set_position(const std::pair<int, int> & position)
{
//	if(position.first < )
}
*/
void Creature::set_max_health(const int state)
{
	if(state <= 0) throw My_Exception("Unavailable max_health state.");
	max_health = state;
}

void Creature::set_health(const int state)
{
	if(state < 0 || state > max_health) throw My_Exception("Unavailable health state.");
	health = state;
}

void Creature::set_damage(const int state)
{
	if(state <= 0) throw My_Exception("Unavailable damage state.");
	damage = state;
}

void Creature::set_damage_probability(const float state)
{
	if(state < 0.1 || state > 1) throw My_Exception("Unavailable damage_probability state.");
	damage_probability = round(state * 100) / 100;
}

void User::correct_next_level()
{
	next_level_experience = (8.52 * exp(0.93 * level));
	max_health = 198 + 109 * level - level * level * 5.87;
	max_mana = 198 + 109 * level - level * level * 5.87;
	damage = 9.85 + 5.67 * level - 0.213 * level * level;
	++skill_point;
}

void User::set_max_mana(const int state)
{
	if(state < 0) throw My_Exception("Unavailable max_mana state.");
	max_mana = state;
}

void User::set_mana(const int state)
{
	if(state < 0 || state > max_mana) throw My_Exception("Unavailable mana state");
	mana = state;
}

void User::set_level(const int state)
{
	if(state < 0) throw My_Exception("Unavailable level state.");
	level = state;
	correct_next_level();
}

void User::set_skill_point(const int state)
{
	if(state < 0) throw My_Exception("Unavalable skill_point state.");
	skill_point = state;
}

int main()
{
	std::srand(std::time(nullptr));
	Creature man;
	man.set_max_health(20);
	man.set_health(15);
	man.set_damage(10);
	man.set_damage_probability(0.9);
	Creature cat(man);
	cat.to_damage(man);
	//man.receive_damage(22, 0.8);
	std::cout << man.get_health() << std::endl;

	Ladder stairs(UP, 8472364782348);
	std::cout << stairs.get_cell_state() << ' ' << stairs.get_ladder_state() << ' ' << stairs.get_offset() << std::endl;


	std::cout << "\n\n\n\n" <<std::endl;


	User user;
	user.set_skill_point(0);
	user.set_level(8);

	std::cout << user.get_max_health() << std::endl;
	std::cout << user.get_damage() << std::endl;
	std::cout << user.get_max_mana() << std::endl;
	std::cout << user.get_level() << std::endl;
	std::cout << user.get_next_level_experience() << std::endl;
	std::cout << user.get_skill_point() << std::endl;

	return 0;
}
