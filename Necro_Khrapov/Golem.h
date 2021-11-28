#ifndef GOLEM_HEADDER
#define GOLEM_HEAEDER

#include "include.h"

class Golem : public Alive_Creature
{
	private:
		int receive_damage_probability;
		golem_states golem_state;
	public:
    	inline int get_recieve_damage_probability() const {return receive_damage_probability;};
    	inline golem_states get_golem_state() const {return golem_state;};

		inline void set_recieve_damage_probability(const int state = 70);
		inline void set_golem_state(const golem_states state);

		void receive_damage(const int magnitude, const int probability);
        void to_damage(Creature & target) const;

        ~Golem() {};
};

#endif