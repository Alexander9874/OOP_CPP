#ifndef CREATURE_HEADER
#define CREATURE_HEADER

#include <utility>
#include <ctime>
#include <cmath>

#include "Dungeon.h"
#include "Cell.h"
#include "exceptions.h"
#include "enums.h"


//enum creature_states {USER, GOBLIN, ORC, OGRE, SUMMONER, GOLEM};

//enum fraction_states {FRIEND, ENEMY, SMTH_ELSE};

class Dungeon;

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
		
		inline void lava_damage();

		inline std::pair<int, int> get_position() const noexcept {return position;};
		inline creature_states get_creature_state() const noexcept {return creature_state;};
		inline int get_max_health() const noexcept {return max_health;};
		inline int get_health() const noexcept {return health;};
		inline fraction_states get_fraction() const noexcept {return fraction;};
		inline int get_damage() const noexcept {return damage;};
		inline int get_damage_probability() const noexcept {return damage_probability;};
		inline bool is_alive() const noexcept {return alive;}
		inline Dungeon * get_dungeon() const noexcept {return dungeon;};

		void set_position(const std::pair<int, int> state);
		void set_creature_state(const creature_states state);
		void set_max_health(const int state);
		void set_health(const int state);
		void set_fraction_state(const fraction_states state);
		void set_damage(const int state);
		void set_damage_probability(const int state);
		inline void set_alive_state(const bool state) noexcept {alive = state;};
		void set_dungeon(Dungeon * state);

		void move_up();									// ???
		void move_down();								// ???
		void move_right();								// ???
		void move_left();								// ???
		void move(const std::pair<int, int> state);		// ???
};

#endif