#ifndef USER_HEADER
#define USER_HEADER

#include "Dungeon_and_Creature.h"
#include "Alive_Creature.h"
#include "Dead_Creature.h"

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
		Creature(USER, mh, FRIEND, d, dp, NONE), max_mana(mm), mana(max_mana), next_level_experience(100), experience(0), level(0), skill_point(0)
		{
			for(int i = 0; i < 4; ++i) skill_table.insert(std::pair<skills, int>(static_cast<skills>(i), 0));
		};
		
		User() :
		Creature(USER, 10, FRIEND, 2, 65, NONE), max_mana(0), mana(0), next_level_experience(100), experience(0), level(0), skill_point(0)
		{
			for(int i = 0; i < 4; ++i) skill_table.insert(std::pair<skills, int>(static_cast<skills>(i), 0));
		};

		~User() = default;

		inline int get_max_mana() const noexcept
		{
			return max_mana;
		};
		inline int get_mana() const noexcept
		{
			return mana;
		};
		inline int get_next_level_experience() const noexcept
		{
			return next_level_experience;
		};
		inline int get_level() const noexcept
		{
			return level;
		};
		inline int get_experience() const noexcept
		{
			return experience;
		};
		inline int get_skill_point() const noexcept
		{
			return skill_point;
		};
		inline int get_skill_power(const skills skill) const
		{
			return skill_table.at(skill);
		};
		inline std::map<skills, int> get_skill_table() const
		{
			return skill_table;
		};

		void set_mana(const int state);
		void set_experience(const int state);
		void set_skill_point(const int state);
		void set_skill_power(const skills skill, const int state);

		void collect_essence();
		void mana_exchange(const int state);
		void receive_experience(const int state);
		void receive_health(const int state);
		void skill_increase(const skills skill_name);

		void wither();
		void curse();
		void necromancy();
		void morphism();

		bool receive_damage(const int magnitude, const int probability);
		void to_damage(Creature * target) const;

		bool turn();
};

#endif
