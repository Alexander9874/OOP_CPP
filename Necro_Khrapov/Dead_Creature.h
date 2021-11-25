#ifndef DEAD_CREATURE_HEADER
#define DEAD_CREATURE_HEADER

#include "include.h"

class Dead_Creature : public Creature
{
	private:
		bool state_increase();
		bool state_decrease();
	protected:
		dead_states dead_state;	
	public:
		Dead_Creature(creature_states st, int mh, int h, fraction_states f, int d, int dp, dead_states ds = GHOST) : Creature(st, mh, h, f, d, dp, false), dead_state(ds) {};
		Dead_Creature(const Alive_Creature & c, dead_states s = GHOST) : Creature(c.creature_state, c.max_health, c.max_health, c.fraction, c.damage, c.damage_probability, false), dead_state(s) {};
		void to_damage(Creature & target) const;
		void receive_damagee(const int magnitude, const int probability);
		dead_states get_dead_state() const {return dead_state;};
		void set_dead_state(const dead_states state) noexcept {dead_state = state;};
		friend class User;
};

#endif