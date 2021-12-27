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

    srand(time(NULL));

    User * user = new User(300, 100, 100, 1);
    user->set_experience(20000);
    user->set_mana(user->get_max_mana() - 3);
    user->receive_damage(150, 100);

    std::cout << user->get_mana() << ' ' << user->get_health() << ' ' << user->get_next_level_experience() << ' ' << user->get_level() << ' ' << user->get_skill_point() << std::endl;
    std::cout << "WITHER " << user->get_skill_power(WITHER) << std::endl;
    std::cout << "CURSE " << user->get_skill_power(CURSE) << std::endl;
    std::cout << "NECROMANCY " << user->get_skill_power(NECROMANCY) << std::endl;
    std::cout << "MORPHISM " << user->get_skill_power(MORPHISM) << std::endl;

    user->skill_increase(MORPHISM);
    user->skill_increase(MORPHISM);
    user->skill_increase(MORPHISM);

    std::cout << "MORPHISM " << user->get_skill_power(MORPHISM) << std::endl;
    std::cout << user->get_skill_point() << std::endl;

    Dungeon dungeon;

    dungeon.set_limits({10, 10});

    //Alive_Creature * creature_1 = new Alive_Creature(GOBLIN, 10, ENEMY, 10, 10); 
    //Alive_Creature * creature_1 = new Alive_Creature(OGRE, 500, FRIEND, 100, 100); 

    //Dead_Creature * creature_2 = new Dead_Creature(OGRE, 500, FRIEND, 100, 100, ZOMBIE);
    Dead_Creature * creature_1 = new Dead_Creature(OGRE, 100, FRIEND, 20, 80, ZOMBIE);

    //Summoner_Alive * creature_1 = new Summoner_Alive(100, FRIEND, 10, 100);

    //Golem * creature_1 = new Golem(100, 20, 90, FIRE, 100);
    //Golem * creature_2 = new Golem(200, 20, 90, FIRE, 50);

    creature_1->set_dungeon(& dungeon);

    creature_1->set_position({6, 2});

    //creature_1->set_position({4, 2});
    //creature_2->set_position({2, 4});
    user->set_position({6, 6});

    //std::cout << creature_1->is_alive() << std::endl;

    //user->to_damage(creature_1);

    //std::cout << creature_1->is_alive() << std::endl;

    //std::cout << user->get_experience() << ' ' << user->get_mana() << ' ' << user->get_health() << std::endl;

    std::cout << "state before" << creature_1->get_dead_state() << std::endl;

    user->morphism();

  //  std::cout << creature_1->is_alive() << std::endl;

//    std::cout << dungeon.get_creature({6, 5})->is_alive() << std::endl;

 //   std::cout << user->get_experience() << ' ' << user->get_mana() << ' ' << user->get_health() << std::endl;

 //   std::cout << creature_1 << ' ' << dungeon.get_creature({6, 5}) << std::endl;

    std::cout << "state after" << creature_1->get_dead_state() << std::endl; 

    //std::vector<std::pair<curse_states, int>> states = creature_1->get_curse_state();
    //std::cout << states.front().first << ' ' << states.front().second << std::endl;

    /*
    dungeon.set_cell({2, 4}, LAVA);
    dungeon.set_cell({4, 2}, LAVA);
    dungeon.set_cell({6, 6}, LAVA);
    */
 /*
    try
    {
        dungeon.turns();
    }
    catch(const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
*/
    //std::cout << dungeon.get_cell_state({3, 3}) << std::endl;
    
    return 0;
}
