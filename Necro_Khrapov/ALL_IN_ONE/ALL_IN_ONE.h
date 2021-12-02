#ifndef DANGEON_HEADER
#define DANGEON_HEADER

#include <map>
#include <utility>
#include <vector>
#include <cmath>
#include <set>

#include "enums.h"
#include "exceptions.h"
#include "Cell.h"

class Dungeon;

class User;

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

		void turn_execute(const std::pair<int, int> direction);

		std::vector<std::pair<int, int>> Lee(const std::pair<int, int> position, const int range, const fraction_states fraction, const search_state search) const;

		virtual void turn()	//Summoner & User edit
		{
			auto steps = Lee(position, 8, !fraction, ALL);
			if(steps.empty()) return;			// steps.size == 0
			auto step = steps.back();			// step = steps.at(step.size)
			
			turn_execute(step);

		}
};

class Dungeon
{
	private:
		std::map<creature_states, Creature *> creature_configuration;

		std::map<std::pair<int, int>, Cell> cells;	////???????
		std::map<std::pair<int, int>, Creature *> creatures;
		User * user;
		std::pair<int, int> limits;
		int level;
		int layer;
	public:

		//~Dungeon() = default;

		Creature * get_configuration(const creature_states state) const;
/*
		void load_layer(const size_t offset = 0);
		void load_map(const char * map_name);
*/		
		void set_cell(std::pair<int, int> position, const cell_states state);
		void set_ladder(std::pair<int, int> position, const size_t offset);
		void set_door(const std::pair<int, int> position);
		void set_limits(const std::pair<int, int> positioin);

		void emplace_creature(std::pair<int, int> position, Creature * creature);

		cell_states get_cell_state(std::pair<int, int> position) const noexcept;
		inline std::pair<int, int> get_limits() const noexcept {return limits;};
		bool is_creature(const std::pair<int, int> position) const;
		Creature * get_creature(const std::pair<int, int> position);
		std::pair<std::pair<int, int>, Creature *> creature_extract(std::pair<int, int> position);

		void cell_remove(std::pair<int, int> position);
		void creature_remove(std::pair<int, int> position);
		void try_emplace_cell(const std::pair<int, int> position, cell_states state);
};

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
		
		std::vector<std::pair<curse_states, int>> get_curse_state() {return curse_state;};
		inline bool is_still_alive() noexcept {return still_alive;};
		
		inline void set_still_alive_state(const bool state = true) noexcept {still_alive = state;}
		
		void add_curse_state(const curse_states state, const int magnitude);
};

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

		~User() = default;

		inline int get_max_mana() const noexcept {return max_mana;};
		inline int get_mana() const noexcept {return mana;};
		inline int get_next_level_experience() const noexcept {return next_level_experience;};
		inline int get_level() const noexcept {return level;};
		inline int get_experience() const noexcept {return experience;};
		inline int get_skill_point() const noexcept {return skill_point;};
		inline int get_skill_power(const skills skill) const {return skill_table.at(skill);};
		inline std::map<skills, int> get_skill_table() const {return skill_table;};

		void set_mana(const int state);
		void set_experience(const int state);
		void set_skill_point(const int state);
		void set_skill_power(const skills skill, const int state);

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

		void turn();
};

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
		
		virtual ~Dead_Creature() = default;

		void to_damage(Creature * target) const;
		bool receive_damage(const int magnitude, const int probability);

		bool dead_state_increase();		//	may be make them private
		bool dead_state_decrease();		//	and friend User???

		inline dead_states get_dead_state() const {return dead_state;};

		void set_dead_state(const dead_states state);
};

class User;

#endif