#ifndef ALIVE_CREATURE_HEADER
#define ALIVE_CREATURE_HEADER

#include "Dungeon_and_Creature.h"

#include <iostream>

class Alive_Creature : public Creature
{
	private:
		std::vector<std::pair<curse_states, int>> curse_state;
	public:
		explicit Alive_Creature(creature_states state) :
		Alive_Creature(*dynamic_cast<Alive_Creature *>(dungeon->get_configuration(state))) {};

		explicit Alive_Creature(creature_states st, int mh, fraction_states f, int d, int dp) :
		Creature(st, mh, f, d, dp, NON_ZERO_HEALTH) {};

		virtual ~Alive_Creature() = default;

		void to_damage(Creature * target) const;
		bool receive_damage(const int magnitude, const int probability);
		
		std::vector<std::pair<curse_states, int>> get_curse_state()
		{
			return curse_state;
		};
		
		void add_curse_state(const curse_states state, const int magnitude);
#include <iostream>		
		virtual bool turn()	//Summoner & User edit
		{
std::cout << "ALIVE?" << std::endl;
			if(is_alive() != NON_ZERO_HEALTH) return false;
			if(lava_damage()) return true;
			if(get_health() == 0)
			{
				set_alive_state(ZERO_HEALTH);
				return false;
			}
			auto steps = Lee(10, ALL, !get_fraction());
			if(steps.empty()) return false;			// steps.size == 0
			auto step = steps.back();				// step = steps.at(step.size)
			turn_execute(step);
			return false;
		}
};

#endif