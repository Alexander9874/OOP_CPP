#ifndef ALIVE_CREATURE_HEADER
#define ALIVE_CREATURE_HEADER

//#include "Dungeon.h"
//#include "Creature.h"

#include "Dungeon_and_Creature.h"

/*
#include "Cell.h"
#include "enums.h"
#include "exceptions.h"
*/


#include <iostream>

class Alive_Creature : public Creature
{
	private:
		std::vector<std::pair<curse_states, int>> curse_state;
		bool still_alive;
	public:
		explicit Alive_Creature(creature_states state) :
		Alive_Creature(*dynamic_cast<Alive_Creature *>(dungeon->get_configuration(state))) {};

		explicit Alive_Creature(creature_states st, int mh, fraction_states f, int d, int dp) :
		Creature(st, mh, f, d, dp, true), still_alive(true) {};

		virtual ~Alive_Creature() = default;

		void to_damage(Creature * target) const;
		bool receive_damage(const int magnitude, const int probability);
		
		std::vector<std::pair<curse_states, int>> get_curse_state()
		{
			return curse_state;
		};
		inline bool is_still_alive() noexcept
		{
			return still_alive;
		};
		
		inline void set_still_alive_state(const bool state = true) noexcept
		{
			still_alive = state;
		}
		
		void add_curse_state(const curse_states state, const int magnitude);
};

#endif