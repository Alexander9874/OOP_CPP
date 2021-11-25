#ifndef USER_HEADER
#define USER_HEADER

#include "include.h"

class User : public Creature
{
	private:
		int max_mana;
		int mana;
		int level;
		int next_level_experience;
		int experience;
		int skill_point;
		std::map<skills, int> skill_table;

		void correct_next_level();
	public:
		int get_max_mana() const noexcept {return max_mana;};
		int get_mana() const noexcept {return mana;};
		int get_level() const noexcept {return level;};
		int get_next_level_experience() const noexcept {return next_level_experience;};
		int get_experience()const noexcept {return experience;};
		int get_skill_point()const noexcept {return skill_point;};
		std::map<skills, int> get_skill_table() const noexcept {return skill_table;};

		void set_max_mana(const int state);
		void set_mana(const int state);
		void set_level(const int state);
		void set_experience(const int state);
/*****/		void set_skill_point(const int state);				/****/
		void set_skill_power(const skills skill, const int state);

		void wither(Creature * target);//+-
		void curse(Creature * target);//+-
		void necromancy(Creature * target);//+-
		void morphism(Creature * target);//+-
		
		void mana_exchange(const int state = 0);//OK
		void receive_experience(const int state = 0);//OK
		void receive_health(const int state = 0);//ok
		void skill_increase(const skills skill_name);
};

#endif
