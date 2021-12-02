#ifndef ENUMS_HEADER
#define ENUMS_HEADER

enum creature_states {USER, GOBLIN, ORC, OGRE, SUMMONER, GOLEM};
// User is always the first & Golem - the last

enum fraction_states {FRIEND, ENEMY, SMTH_ELSE};

enum cell_states {FLOOR, WALL, LAVA, DOOR_OPENED, DOOR_CLOSED, LADDER, ESSENCE};

//enum ladder_states {UP, DOWN}; // completed

enum skills {WITHER, CURSE, NECROMANCY, MORPHISM};  //  completed

enum curse_states {SPEED, SLOWNESS, STRENGTH, WEAKNESS, RESISTANCE, MORTIFICATION, ACCURACY, INACCURACY, DODGE, CLUMSINESS};
/*                  0      0 + true  1         1 + true  2           2 + true       3         3 + true    4      4 + true */     

enum golem_states {ETHER, FIRE, STONE};
// Do not change order 

enum dead_states {GHOST, SKELETON, MUMMY, ZOMBIE, GHOUL, VAMPIRE}; 
// Ghost is always the first & Vampire - tte last
// https://en.wikipedia.org/wiki/Undead

#endif