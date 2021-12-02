#include "ALL_IN_ONE.h"

#include <iostream>

int main()
{
    Dungeon dungeon;
    
    User user(10, 10, 70, -1);  ///!!!! -1 -> exception

    dungeon.emplace_creature(std::pair<int, int>(0, 0), static_cast<Creature *>(& user));

    user.set_dungeon(& dungeon);

    user.set_experience(500);

    std::cout << user.get_max_health() << std::endl;
    std::cout << user.get_max_mana() << std::endl;
    std::cout << user.get_skill_point() << std::endl;

    user.skill_increase(WITHER);

    std::cout << user.get_skill_point() << std::endl;

    user.set_skill_power(NECROMANCY, 5);


    return 0;
}