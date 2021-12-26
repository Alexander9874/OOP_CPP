#include "Dungeon_and_Creature.h"
#include "Alive_Creature.h"
#include "Dead_Creature.h"
#include "Summoner.h"
#include "Golem.h"
#include "User.h"
#include "Cell.h"

#include <iostream>

int main()
{
    User * user = new User(100, 10, 80, 1);

    Dungeon dungeon;

    dungeon.set_limits({10, 10});

    //Alive_Creature * creature_2 = new Alive_Creature(GOBLIN, 500, ENEMY, 10, 100); 
    Alive_Creature * creature_1 = new Alive_Creature(SUMMONER, 100, FRIEND, 10, 100); 

    //Dead_Creature * creature_1 = new Dead_Creature(OGRE, 500, ENEMY, 20, 80, ZOMBIE);
    //Dead_Creature * creature_2 = new Dead_Creature(OGRE, 100, FRIEND, 20, 80, VAMPIRE);

    creature_1->set_dungeon(& dungeon);

    creature_1->set_position({4, 2});
    //creature_2->set_position({2, 4});
    user->set_position({6, 6});

    try
    {
        dungeon.turns();
    }
    catch(const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}