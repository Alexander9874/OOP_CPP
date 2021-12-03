#include "Dungeon_and_Creature.h"
#include "Alive_Creature.h"
#include "Dead_Creature.h"
#include "Summoner.h"
#include "Golem.h"
#include "User.h"
#include "Cell.h"

int main()
{
    //User * user = new User(10, 10, 80, 1);

    Dungeon dungeon;

    Alive_Creature * creature = new Alive_Creature(GOBLIN, 100, ENEMY, 10, 60); 

    creature->add_curse_state(SLOWNESS, 1);

    creature->set_dungeon(& dungeon);

    dungeon.emplace_creature(std::pair<int, int>(0, 0), creature);

    dungeon.creature_remove(std::pair<int, int>(0, 0));

//    delete user;

    return 0;
}