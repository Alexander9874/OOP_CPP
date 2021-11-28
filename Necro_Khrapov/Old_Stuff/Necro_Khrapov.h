#ifndef NECRO_KHRAPOV_HEADER
#define NECRO_KHRAPOV_HEADER

#include <vector>
#include <map>
#include <utility>
#include <cmath>
#include <ctime>
#include <limits>

#include "My_Exception.h"

enum creature_states {USER, ORC, GOBLIN, OGRE, SUMMONER};

enum fraction_states {FRIEND, ENEMY, SMTH_ELSE};

enum cell_states {WALL, LAVA, DOOR_OPENED, DOOR_CLOSED, LADDER, ESSENCE};

enum ladder_states {UP, DOWN};

enum skills {WITHER, CURSE, NECROMANCY, MORPHISM};

enum curse_states {SLOWNESS, WEAKNESS, SPEED, STRENGTH};

enum golem_states {STONE, FIRE, ETHER};

enum dead_states {SKELETON, ZOMBIE, GHOST};

class Cell
{
	private:
		cell_states cell_state;
	public:
		Cell(cell_states state) : cell_state(state) {};
[[nodiscard]]	cell_states get_cell_state() const noexcept {return cell_state;};
		void set_cell_state(const cell_states state) noexcept {cell_state = state;};
};

class Ladder : public Cell
{
	private:
		ladder_states ladder_state;
		size_t offset;
	public:
		Ladder(ladder_states b, size_t c) : Cell(LADDER), ladder_state(b), offset(c) {};
[[nodiscard]]	ladder_states get_ladder_state() const noexcept {return ladder_state;};
[[nodiscard]]	size_t get_offset() const noexcept {return offset;};
		
		void set_ladder_state(const ladder_states state) noexcept {ladder_state = state;};
		void set_offset(const size_t state) noexcept {offset = state;};
};

class Creature
{
	protected:
		creature_states creature_state;
		std::pair<int, int> position;
		int max_health;
		int health;
		fraction_states fraction;
		int damage;
		float damage_probability;
	public:
		/*Creature(creature_states st, std::pair<int, int> pos, int mh, int d, int dp, fraction_states f = ENEMY, int h = std::numeric_limits<int>::max()) : creature_state(st), position(pos), max_health(mh), damage(d), damage_probability(dp), fraction(f), health(h)
		{
			if()
		};*/
		virtual void receive_damage(const int magnitude, const float probability)
		{
			if(magnitude <= 0) throw My_Exception("Unavailable damage received.");
			if(probability > 1 || probability < 0.1) throw My_Exception("Unavailable damage_probability received.");
			if(std::rand() % 100 < probability * 100)
			{
				health -= magnitude;
				if(health < 0) health = 0;
			}
		};
		void to_damage(Creature & target) const {target.receive_damage(damage, damage_probability);};
		
[[nodiscard]]	fraction_states get_fraction() const noexcept {return fraction;};
[[nodiscard]]	std::pair<int, int> get_position() const noexcept {return position;};
[[nodiscard]]	int get_max_health() const noexcept {return max_health;};
[[nodiscard]]	int get_health() const noexcept {return health;};
[[nodiscard]]	int get_damage() const noexcept {return damage;};
[[nodiscard]]	float get_damage_probability() const noexcept {return damage_probability;};
[[nodiscard]]	creature_states get_creature_state() const noexcept {return creature_state;};

		void set_fraction_state(const fraction_states state) noexcept {fraction = state;} ;
		void set_position(const std::pair<int, int> & position);/*here*/
		void set_max_health(const int state);
		void set_health(const int state);
		void set_damage(const int state);
		void set_damage_probability(const float state);
		void set_creature_state(const creature_states state) noexcept {creature_state = state;};

};

class User : public Creature
{
	private:
		int max_mana;
		int mana;
		int level;
		int next_level_experience;
		int experience;
		int skill_point;
		std::map<skills, int> skill_table;

		void correct_next_level();
	public:
[[nodiscard]]	int get_max_mana() const noexcept {return max_mana;};
[[nodiscard]]	int get_mana() const noexcept {return mana;};
[[nodiscard]]	int get_level() const noexcept {return level;};
[[nodiscard]]	int get_next_level_experience() const noexcept {return next_level_experience;};
[[nodiscard]]	int get_experience()const noexcept {return experience;};
[[nodiscard]]	int get_skill_point()const noexcept {return skill_point;};
[[nodiscard]]	std::map<skills, int> get_skill_table() const noexcept {return skill_table;};

		void set_max_mana(const int state);
		void set_mana(const int state);
		void set_level(const int state);
		void set_experience(const int state);
/*****/		void set_skill_point(const int state);				/****/
		void set_skill_power(const skills skill, const int state);
		void set_skill_table(const std::map<skills, int> state);

		void wither(Creature & target);
		void curse(Creature & target);
		void necromancy(Creature & target);
		void morphism(Creature & target);
		void mana_exchange(const int state = 0);
		void next_level();
		void receive_experience(const int state = 0);
		void skill_point_exchange(const int state);
		void skill_increase(const skills skill_name);
};

class Alive_Creature : public Creature
{
	private:
		std::vector<std::pair<curse_states, int>> curse_state;
		bool alive;
	public:
[[nodiscard]]	std::vector<std::pair<curse_states, int>> get_curse_state() const {return curse_state;};
[[nodiscard]]	bool is_alive() {return alive;};
		void set_curse_state(const std::vector<std::pair<curse_states, int>> state) noexcept {curse_state = state;};
		void set_alive(const bool state = true) noexcept {alive = state;}
		void add_curse_state(const curse_states state, const int magnitude);
		void add_curse_state(std::pair<curse_states, int> state);
		void necromancy();

};

class Dead_Creature : public Creature
{
	private:
		dead_states dead_state;
	public:
[[nodiscard]]	dead_states get_dead_state() const {return dead_state;};
		void set_dead_state(const dead_states state) noexcept {dead_state = state;};
};

class Golem : public Alive_Creature
{
	private:
		float receive_damage_probability;
		golem_states golem_state;
	public:
[[nodiscard]]	float get_recieve_damage_probability() const {return receive_damage_probability;};
[[nodiscard]]	golem_states get_golem_state() const {return golem_state;};

		void set_recieve_damage_probability(const float state =0.7);
		void set_golem_state(const golem_states state) noexcept {golem_state = state;};

		void receive_damage(const int magnitude, const float probability);
};

class Summoner_Alive : public Alive_Creature
{
	public:
		void summone();
};

class Summoner_Dead : public Dead_Creature
{
	public:
		void summone();
};

class Dangeon
{
	private:
		std::map<std::pair<int, int>, Cell> field;
		std::vector<Creature> creatures;
		User user;
		int level;
		int layer;
	public:
		void load_layer(const size_t offset = 0);
		void load_map(const char * map_name);
		
[[nodiscard]]	std::map<std::pair<int, int>, Cell> get_field() const noexcept {return field;};
		
		void set_cell(std::pair<int, int> position, const cell_states cell);
		void set_cell(Cell & cell, const cell_states state);
		void set_ladder(Ladder & cell, const ladder_states state, const size_t offset);
		void set_ladder(const std::pair<int, int> position, ladder_states state, size_t offset);
		void set_door(const std::pair<int, int> position);
		void set_door(const Cell & door);
};

#endif
