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
    ///Alive_Creature * creature_1 = new Alive_Creature(OGRE, 100, FRIEND, 10, 100); 

    Dead_Creature * creature_1 = new Dead_Creature(OGRE, 500, ENEMY, 20, 80, ZOMBIE);
   // Dead_Creature * creature_2 = new Dead_Creature(OGRE, 100, FRIEND, 20, 80, VAMPIRE);

    //creature_1->add_curse_state(SLOWNESS, 1);

    creature_1->set_dungeon(& dungeon);
    //user->set_dungeon(& dungeon);
/*    try
    {
        dungeon.emplace_creature({100, 100}, creature);
    }
    catch(std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
*/
    //std::cout << dungeon.is_creature({8, 8}) << ' ' << dungeon.get_cell_state({8, 8}) << std::endl;
    //std::cout << dungeon.is_creature({0, 0}) << ' ' << dungeon.get_cell_state({0, 0}) << std::endl;


    creature_1->set_position({4, 2});
    //creature_2->set_position({2, 4});
    //std::cout << dungeon.is_creature({8, 8}) << ' ' << dungeon.get_cell_state({8, 8}) << std::endl;
    //std::cout << dungeon.is_creature({0, 0}) << ' ' << dungeon.get_cell_state({0, 0}) << std::endl;
    user->set_position({6, 6});

    //dungeon.emplace_creature({8, 8}, creature);
    //dungeon.emplace_creature({0, 0}, user);
    try{
        //while(1) dungeon.get_creature({0, 0})->turn();
        while(1)
        {
            if(creature_1) creature_1->turn();
          //  if(creature_2) creature_2->turn();
            if(creature_1) std::cout << "Creauture_1: " << creature_1->get_position().first << ' ' << creature_1->get_position().second << ' ' << creature_1->get_health() << std::endl;
           // if(creature_2) std::cout << "Creauture_2: " << creature_2->get_position().first << ' ' << creature_2->get_position().second << ' ' << creature_2->get_health() << std::endl;
            std::cout << "User health: " << user->get_health() << std::endl;
            
        }
    }
    catch(std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }   
    //dungeon.creature_remove(std::pair<int, int>(0, 0));

//    delete user;

    return 0;
}