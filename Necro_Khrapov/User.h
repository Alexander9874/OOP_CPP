#ifndef USER_HEADER
#define USER_HEADER

#include <map>
#include <utility>
#include <vector>

#include "Creature.h"
#include "Alive_Creature.h"
#include "Dead_Creature.h"
#include "Cell.h"
#include "enums.h"

//enum skills {WITHER, CURSE, NECROMANCY, MORPHISM};

class Dungeon;

class Creature;

class Alive_Creature;

class Dead_Creature;

class User : public Creature
{
	private:
		int max_mana;
		int mana;
		int next_level_experience; // 0th -> 1st level 100 exp
		int experience;
		int level;
		int skill_point;
		std::map<skills, int> skill_table;

		void correct();
		
	public:
		explicit User(int mh, int d, int dp, int mm) :
		Creature(USER, mh, FRIEND, d, dp, false), max_mana(mm), mana(max_mana), next_level_experience(100), experience(0), level(0), skill_point(0)
		{
			for(int i = 0; i < 4; ++i) skill_table.insert(std::pair<skills, int>(static_cast<skills>(i), 0));
		};
		
		User() :
		Creature(USER, 10, FRIEND, 2, 65, false), max_mana(0), mana(0), next_level_experience(100), experience(0), level(0), skill_point(0)
		{
			for(int i = 0; i < 4; ++i) skill_table.insert(std::pair<skills, int>(static_cast<skills>(i), 0));
		};

		inline int get_max_mana() const noexcept {return max_mana;};
		inline int get_mana() const noexcept {return mana;};
		inline int get_next_level_experience() const noexcept {return next_level_experience;};
		inline int get_level() const noexcept {return level;};
		inline int get_experience() const noexcept {return experience;};
		inline int get_skill_point() const noexcept {return skill_point;};
		inline int get_skill_power(const skills skill) const {return skill_table.at(skill);};
		inline std::map<skills, int> get_skill_table() const {return skill_table;};

		inline void set_mana(const int state);
		void set_experience(const int state);
		inline void set_skill_point(const int state);
		inline void set_skill_power(const skills skill, const int state);


		void collect_essence();
		void mana_exchange(const int state);
		void receive_experience(const int state);
		void receive_health(const int state);
		void skill_increase(const skills skill_name);

		void wither(Creature * target);
		void curse(Creature * target);
		void necromancy(Creature * target);
		void morphism(Creature * target);

		bool receive_damage(const int magnitude, const int probability);
		void to_damage(Creature * target) const;
};

#endif
