#ifndef NECRO_KHRAPOV_HEADER
#define NECRO_KHRAPOV_HEADER

enum creature_states {USER, ORC, GOBLIN, OGRE, SUMMONER};

enum fraction_states {FRIEND, ENEMY, SMTH_ELSE};

enum cell_states {WALL, LAVA, DOOR_OPENED, DOOR_CLOSED, LADDER, ESSENCE};

enum ladder_states {UP, DOWN};

enum skills {WITHER, CURSE, NECROMANCY, MORPHISM};

enum curse_state {SLOWNESS, WEAKNESS, SPEED, STRENGTH};

enum golem_states {STONE, FIRE, ETHER};

enum dead_states {SKELETON, ZOMBIE, GHOST};

class Dangeon
{
};

class Cell
{
};

class Ladder : public Cell
{
};

class Creature
{
};

class Player : public Creature
{
};

class Alive_Creature : public Creature
{
};

class Dead_Creature : public Creature
{
};

class Golem : public Alive_Creature
{
};

class Summoner_Alive : public Alive_Creature
{
};

class Summoner_Dead : public Dead_Creature
{
};

#endif
