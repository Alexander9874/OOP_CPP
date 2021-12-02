#ifndef DEAD_CREATURE_HEADER
#define DEAD_CREATURE_HEADER

#include <utility>

#include "Creature.h"
#include "Alive_Creature.h"
#include "Cell.h"
#include "Dungeon.h"
#include "enums.h"

//enum dead_states {GHOST, SKELETON, MUMMY, ZOMBIE, GHOUL, VAMPIRE}; 

class Dungeon;

//class Creature;

class Alive_Creature;

class Dead_Creature : public Creature
{
	private:
		dead_states dead_state;
	public:

		explicit Dead_Creature(creature_states alive_state, dead_states dead_state) : 
		Dead_Creature(*(dynamic_cast<Alive_Creature *>(dungeon->get_configuration(alive_state))), dead_state) {};

		explicit Dead_Creature(creature_states st, int mh, fraction_states f, int d, int dp, dead_states ds = GHOST) :
		Creature(st, mh, f, d, dp, false), dead_state(ds) {};

		explicit Dead_Creature(const Alive_Creature & c, dead_states s = GHOST) :
		Creature(c.get_creature_state(), c.get_max_health(), c.get_fraction(), c.get_damage(), c.get_damage_probability(), false), dead_state(s) {};
		
		void to_damage(Creature * target) const;
		bool receive_damage(const int magnitude, const int probability);

		bool dead_state_increase();		//	may be make them private
		bool dead_state_decrease();		//	and friend User???

		inline dead_states get_dead_state() const {return dead_state;};

		inline void set_dead_state(const dead_states state);
};

#endif