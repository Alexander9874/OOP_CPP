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

enum alive_states
{
    NONE,               // 0
    NON_ZERO_HEALTH,    // 1
    ZERO_HEALTH,        // 2
    ALL                 // 3
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

inline fraction_states operator ! (fraction_states fraction) noexcept
{
    if(fraction == FRIEND) return ENEMY;
    return FRIEND;
}

dead_states & operator ++ (dead_states & state); // ++state

dead_states & operator -- (dead_states & state); // --state

dead_states operator ++ (dead_states & state, int); // state++

dead_states operator -- (dead_states & state, int); // state--

#endif