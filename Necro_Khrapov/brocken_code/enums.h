#ifndef ENUMS_HEADER
#define ENUMS_HEADER

#include "exceptions.h"

// User is always the first & Golem - the last
enum creature_states
{
    USER,       // 0
    GOBLIN,     // 1
    ORC,        // 2
    OGRE,       // 3
    SUMMONER,   // 4
    GOLEM       // 5
};

enum fraction_states
{
    FRIEND, // 0
    ENEMY   // 1
};

enum cell_states
{
    FLOOR,          // 0
    WALL,           // 1
    LAVA,           // 2
    DOOR_OPENED,    // 3
    DOOR_CLOSED,    // 4
    LADDER,         // 5
    ESSENCE         // 6
};

//enum ladder_states {UP, DOWN}; // completed

enum skills
{
    WITHER,     // 0
    CURSE,      // 1
    NECROMANCY, // 2
    MORPHISM    // 3
};

enum curse_states
{
    SPEED,          // 0 = 0 * 2
    SLOWNESS,       // 1 = 0 * 2 + true
    STRENGTH,       // 2 = 1 * 2
    WEAKNESS,       // 3 = 1 * 2 + true
    RESISTANCE,     // 4 = 2 * 2
    MORTIFICATION,  // 5 = 2 * 2 + true
    ACCURACY,       // 6 = 3 * 2 
    INACCURACY,     // 7 = 3 * 2 + true
    DODGE,          // 8 = 4 * 2 
    CLUMSINESS      // 9 = 4 * 2 + true
};

// Do not change, EVEN order 
enum golem_states
{
    ETHER,  // 0
    FIRE,   // 1
    STONE   // 2
};

// Ghost is always the first & Vampire - the last
// https://en.wikipedia.org/wiki/Undead
enum dead_states
{
    GHOST,      // 0
    SKELETON,   // 1
    MUMMY,      // 2
    ZOMBIE,     // 3
    GHOUL,      // 4
    VAMPIRE     // 5
}; 

enum search_state
{
    ALL,    // 0
    ALIVE,  // 1
    DEAD    // 2
};

inline fraction_states operator ! (fraction_states fraction) noexcept
{
    if(fraction == FRIEND) return ENEMY;
    return FRIEND;
}

dead_states & operator ++ (dead_states & state); // ++state

dead_states & operator -- (dead_states & state); // --state

dead_states operator ++ (dead_states & state, int); // state++

dead_states operator -- (dead_states & state, int); // state--

/*
inline fraction_states operator ! (fraction_states fraction) noexcept
{
    if(fraction == FRIEND) return ENEMY;
    return FRIEND;
}

dead_states & operator ++ (dead_states & state) // ++state
{
    if(state == VAMPIRE) throw Exception("already_max_state");
    state = static_cast<dead_states>(static_cast<int>(state) + 1);
    return state;
}

dead_states & operator -- (dead_states & state) // --state
{
    if(state == GHOST) throw Exception("already_min_state");
    state = static_cast<dead_states>(static_cast<int>(state) - 1);
    return state;
}

dead_states operator ++ (dead_states & state, int) // state++
{
    if(state == VAMPIRE) throw Exception("already_max_state");
    dead_states tmp = state;
    state = static_cast<dead_states>(static_cast<int>(state) + 1);
    return tmp;
}

dead_states operator -- (dead_states & state, int) // state--
{
    if(state == GHOST) throw Exception("already_min_state");
    dead_states tmp = state;
    state = static_cast<dead_states>(static_cast<int>(state) - 1);
    return tmp;
}
*/
#endif