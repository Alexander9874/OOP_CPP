#ifndef CREATURE_HEADER
#define CREATURE_HEADER

#include <utility>
#include <set>
#include <ctime>
#include <cmath>
#include <vector>

#include "Dungeon.h"
#include "Cell.h"
#include "enums.h"
#include "exceptions.h"

template <typename X, typename Y>                                                   
inline std::pair<X, Y> operator + (const std::pair<X, Y> & first, const std::pair<X, Y> & second)
{   
    return std::pair<X, Y>(first.first + second.first, first.second + second.second);
}

template <typename X, typename Y>                                                   
inline std::pair<X, Y> operator - (const std::pair<X, Y> & first, const std::pair<X, Y> & second)
{   
    return std::pair<X, Y>(first.first - second.first, first.second - second.second);
}

class Creature
{
	private:
		std::pair<int, int> position; //	(x, y) x: right & left, y: up & down
		creature_states creature_state;
		int max_health;
		int health;
		fraction_states fraction;
		int damage;
		int damage_probability;
		bool alive;
	protected:
		static Dungeon * dungeon;
	public:
		// ADD POSITION TO CONSTRUCTOR
		explicit Creature(creature_states st, int mh, fraction_states f, int d, int dp, bool a) :
		creature_state(st), max_health(mh), health(max_health), fraction(f), damage(d), damage_probability(dp), alive(a)
		{
			if(max_health < 0) throw Exception("unavailable_value");
			if(damage < 0) throw Exception("unavailable_value");
			if(damage_probability < 0 || damage_probability > 100) throw Exception("unavailable_value");
		}

		virtual ~Creature() = default;

		virtual bool receive_damage(const int magnitude, const int probability) = 0;
 		virtual void to_damage(Creature * target) const = 0;
		
		inline void lava_damage()
		{
			if(dungeon->get_cell_state(get_position()) == LAVA) receive_damage(30, 100);
		};
		inline std::pair<int, int> get_position() const noexcept
		{
			return position;
		};
		inline creature_states get_creature_state() const noexcept
		{
			return creature_state;
		};
		inline int get_max_health() const noexcept
		{
			return max_health;
		};
		inline int get_health() const noexcept
		{
			return health;
		};
		inline fraction_states get_fraction() const noexcept
		{
			return fraction;
		};
		inline int get_damage() const noexcept{
			return damage;
		};
		inline int get_damage_probability() const noexcept
		{
			return damage_probability;
		};
		inline bool is_alive() const noexcept
		{
			return alive;
		}
		inline Dungeon * get_dungeon() const noexcept
		{
			return dungeon;
		};

		void set_position(const std::pair<int, int> state);
		void set_creature_state(const creature_states state);
		void set_max_health(const int state);
		void set_health(const int state);
		void set_fraction_state(const fraction_states state);
		void set_damage(const int state);
		void set_damage_probability(const int state);
		inline void set_alive_state(const bool state) noexcept
		{
			alive = state;
		};
		void set_dungeon(Dungeon * state);

		void turn_execute(const std::pair<int, int> direction);

		std::vector<std::pair<int, int>> Lee( const int range, const search_state search, const fraction_states _fraction) const;

		virtual void turn()	//Summoner & User edit
		{
			auto steps = Lee(8, ALL, !fraction);
			if(steps.empty()) return;			// steps.size == 0
			auto step = steps.back();			// step = steps.at(step.size)
			
			turn_execute(step);

		}
};

#endif