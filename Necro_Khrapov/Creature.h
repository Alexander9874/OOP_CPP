#ifndef CREATURE_HEADER
#define CREATURE_HEADER

#include "include.h"

class Creature
{
	private:
		creature_states creature_state;
		int max_health;
		int health;
		fraction_states fraction;
		int damage;
		int damage_probability;
		bool alive;		// can be replaced with dynamic_cast inside other codes
	public:
		explicit Creature(creature_states st, int mh, fraction_states f, int d, int dp, bool a) :
		creature_state(st), max_health(mh), health(max_health), fraction(f), damage(d), damage_probability(dp), alive(a)
		{
			if(max_health < 0) throw Exception("unavailable_value");
			if(damage < 0) throw Exception("unavailable_value");
			if(damage_probability < 0 || damage_probability > 100) throw Exception("unavailable_value");
		}

		Creature() :
		creature_state(GOBLIN), max_health(0), health(0), fraction(ENEMY), damage(0), damage_probability(0), alive(false) {}; 

/*
 *		virtual void receive_damage(const int magnitude, const int probability)
 *		{
 *			if(magnitude < 0) throw Exception("unavailable_value"); 
 *			if(probability > 100 || probability < 0) throw Exception("unavailable_value");
 *			if(std::rand() % 100 < probability)
 *			{
 *				health -= magnitude;
 *				if(health < 0) health = 0;
 *			}
 *		}
 *
 *		virtual void to_damage(Creature & target) const
 *		{
 *			if(this == & target) throw Exception("self_harm");
 *			if(fraction == target.fraction) throw Exception("frendly_fire");
 *			target.receive_damage(damage, damage_probability);
 *		}
 */

		virtual void receive_damage(const int magnitude, const int probability) = 0;

 		virtual void to_damage(Creature & target) const = 0;

		inline creature_states get_creature_state() const noexcept {return creature_state;};
		inline int get_max_health() const noexcept {return max_health;};
		inline int get_health() const noexcept {return health;};
		inline fraction_states get_fraction() const noexcept {return fraction;};
		inline int get_damage() const noexcept {return damage;};
		inline int get_damage_probability() const noexcept {return damage_probability;};
		inline bool is_alive() noexcept {return alive;}

		inline void set_creature_state(const creature_states state);
		inline void set_max_health(const int state);
		inline void set_health(const int state);
		inline void set_fraction_state(const fraction_states state);
		inline void set_damage(const int state);
		inline void set_damage_probability(const float state);
		inline void set_alive_state(const bool state) noexcept {alive = state;};
};

#endif