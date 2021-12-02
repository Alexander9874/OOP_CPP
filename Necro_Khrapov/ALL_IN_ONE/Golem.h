#ifndef GOLEM_HEADDER
#define GOLEM_HEAEDER

#include "ALL_IN_ONE.h"
//#include "enums.h"

//enum golem_states {ETHER, FIRE, STONE};

class Golem : public Creature
{
	private:
		int receive_damage_probability;
		golem_states golem_state;
	public:

		explicit Golem(int mh, int d, int dp, golem_states gs, int rdp) :
		Creature(GOLEM, mh, ENEMY, d, dp, false), receive_damage_probability(rdp), golem_state(gs) {};

		explicit Golem(golem_states state) : 
		Golem(*(dynamic_cast<Golem *>(dungeon->get_configuration(GOLEM))))
		{
			golem_state = state;
		}

    	inline int get_recieve_damage_probability() const {return receive_damage_probability;};
    	inline golem_states get_golem_state() const {return golem_state;};

		inline void set_recieve_damage_probability(const int state);
		inline void set_golem_state(const golem_states state);

		bool receive_damage(const int magnitude, const int probability);
        void to_damage(Creature * target) const;

        ~Golem()
		{
			cell_states cell;
			if(golem_state == ETHER) cell = ESSENCE;
			if(golem_state == FIRE) cell = LAVA;
			else cell = WALL;
			dungeon->try_emplace_cell(get_position(), cell);
		};
};

#endif