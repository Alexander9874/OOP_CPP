#ifndef ENUMS_HEADER
#define ENUMS_HEADER

#include "exceptions.h"

enum creature_states {USER, GOBLIN, ORC, OGRE, SUMMONER, GOLEM};
// User is always the first & Golem - the last

enum fraction_states {FRIEND, ENEMY};

enum cell_states {FLOOR, WALL, LAVA, DOOR_OPENED, DOOR_CLOSED, LADDER, ESSENCE};

//enum ladder_states {UP, DOWN}; // completed

enum skills {WITHER, CURSE, NECROMANCY, MORPHISM};  //  completed

enum curse_states {SPEED, SLOWNESS, STRENGTH, WEAKNESS, RESISTANCE, MORTIFICATION, ACCURACY, INACCURACY, DODGE, CLUMSINESS};
/*                  0      0 + true  1         1 + true  2           2 + true       3         3 + true    4      4 + true */     

enum golem_states {ETHER, FIRE, STONE};
// Do not change 

enum dead_states {GHOST, SKELETON, MUMMY, ZOMBIE, GHOUL, VAMPIRE}; 
// Ghost is always the first & Vampire - the last
// https://en.wikipedia.org/wiki/Undead

enum search_state {ALL, ALIVE, DEAD};

inline fraction_states operator ! (fraction_states fraction) noexcept
{
    if(fraction == FRIEND) return ENEMY;
    return FRIEND;
}

inline dead_states & operator ++ (dead_states & state) // ++state
{
    if(state == VAMPIRE) throw Exception("already_max_state");
    state = static_cast<dead_states>(static_cast<int>(state) + 1);
    return state;
}

inline dead_states & operator -- (dead_states & state) // --state
{
    if(state == GHOST) throw Exception("already_min_state");
    state = static_cast<dead_states>(static_cast<int>(state) - 1);
    return state;
}

inline dead_states operator ++ (dead_states & state, int) // state++
{
    if(state == VAMPIRE) throw Exception("already_max_state");
    dead_states tmp = state;
    state = static_cast<dead_states>(static_cast<int>(state) + 1);
    return tmp;
}

inline dead_states operator -- (dead_states & state, int) // state--
{
    if(state == GHOST) throw Exception("already_min_state");
    dead_states tmp = state;
    state = static_cast<dead_states>(static_cast<int>(state) - 1);
    return tmp;
}

#endif