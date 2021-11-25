#ifndef SUMMONER_HEADER
#define SUMMONER_HEADER

#include "include.h"

class Summoner
{
    protected:
        int summon_probability;
    public:
        Summoner(int sp) : summon_probability(sp) {};
        virtual void summon() = 0;
};

class Summoner_Alive : public Alive_Creature, public Summoner
{
    public:
		Summoner_Alive(int mh, int h, fraction_states f, int d, int dp, int sp, bool sa = true) : Alive_Creature(SUMMONER, mh, h, f, d, dp, sa), Summoner(sp) {};
        void summon();
        friend class Summoner_Dead;
};

class Summoner_Dead : public Dead_Creature, public Summoner
{
    public:
		Summoner_Dead(int mh, int h, fraction_states f, int d, int dp, int sp, dead_states ds = GHOST) : Dead_Creature(SUMMONER, mh, h, f, d, dp, ds), Summoner(sp) {};
   		Summoner_Dead(const Summoner_Alive & c, dead_states ds = GHOST) : Dead_Creature(SUMMONER, c.max_health, c.max_health, c.fraction, c.damage, c.damage_probability, ds), Summoner(c.summon_probability) {};
        void summon();
};

#endif