#ifndef SUMMONER_HEADER
#define SUMMONER_HEADER

#include "Alive_Creature.h"
#include "Dead_Creature.h"

class Summoner
{
    protected:
        int summon_probability;
    public:
        Summoner(int sp = 10) :
        summon_probability(sp)
        {
            if(summon_probability < 0 || summon_probability > 100) throw Exception("unavailable_value");
        };
        
        virtual ~Summoner() = default;

        virtual void summon() = 0;

        inline int get_summon_probability() const noexcept
        {
            return summon_probability;
        };
        
        void set_summon_probability(const int state);
};

class Summoner_Alive : public Alive_Creature, public Summoner
{
    public:
		Summoner_Alive(int mh, fraction_states f, int d, int dp, int sp = 10) :
        Alive_Creature(SUMMONER, mh, f, d, dp), Summoner(sp) {};

        ~Summoner_Alive() = default;

        void summon();

        void turn();
};

class Summoner_Dead : public Dead_Creature, public Summoner
{
    public:
		Summoner_Dead(int mh, fraction_states f, int d, int dp, int sp, dead_states ds = GHOST) :
        Dead_Creature(SUMMONER, mh, f, d, dp, ds), Summoner(sp) {};

   		Summoner_Dead(const Summoner_Alive & c, dead_states ds = GHOST) :
        Dead_Creature(SUMMONER, c.get_max_health(), c.get_fraction(), c.get_damage(), c.get_damage_probability(), ds), Summoner(c.get_summon_probability()) {};

        ~Summoner_Dead() = default;

        void summon();

        void turn();
};

#endif