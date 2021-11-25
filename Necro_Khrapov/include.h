#ifndef SUPER_HEADER_FILE
#define SUPER_HEADER_FILE

#include <vector>
#include <exception>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <map>
#include <utility>
#include <limits>

#include "Cell.h"
#include "Alive_Creature.h"
#include "Dangeon.h"
#include "Dead_Creature.h"
#include "exceptions.h"
#include "Summoner.h"
#include "User.h"
#include "Creature.h"
#include "Golem.h"

enum creature_states {NONE, USER, ORC, GOBLIN, OGRE, SUMMONER};

enum fraction_states {FRIEND, ENEMY, SMTH_ELSE};

enum cell_states {WALL, LAVA, DOOR_OPENED, DOOR_CLOSED, LADDER, ESSENCE};

enum ladder_states {UP, DOWN}; // completed

enum skills {WITHER, CURSE, NECROMANCY, MORPHISM};  //  completed

enum curse_states {SPEED, SLOWNESS, STRENGTH, WEAKNESS, RESISTANCE, MORTIFICATION, ACCURACY, INACCURACY, DODGE, CLUMSINESS};
/*                  0      0 + true  1         1 + true  2           2 + true       3         3 + true    4      4 + true */     

enum golem_states {STONE, FIRE, ETHER}; // completed

enum dead_states {GHOST, SKELETON, ZOMBIE, GHOUL};

#endif