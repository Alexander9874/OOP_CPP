#ifndef ALIVE_CREATURE_HEADER
#define ALIVE_CREATURE_HEADER

#include "include.h"

class Alive_Creature : public Creature
{
	protected:
		std::vector<std::pair<curse_states, int>> curse_state;
		bool still_alive;
	public:
		Alive_Creature(creature_states st, int mh, int h, fraction_states f, int d, int dp, bool sa = true) : Creature(st, mh, h, f, d, dp, true), still_alive(sa) {};
		void to_damage(Creature & target) const;
		void receive_damage(const int magnitude, const int probability);
		bool is_still_alive() {return alive;};
		void set_alive(const bool state = true) noexcept {alive = state;}
		void add_curse_state(const curse_states state, const int magnitude);
		friend class Dead_Creature;
};

#endif