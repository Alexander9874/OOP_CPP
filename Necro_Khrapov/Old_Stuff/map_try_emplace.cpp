#include <map>
#include <iostream>

int main()
{
    std::map<int, int> table;
    table.emplace(1, 1);

    table.try_emplace(1, 5);
    table.try_emplace(2, 4);
    table.try_emplace(2, 4);
    table.try_emplace(23, 42343);


    for(std::map<int, int>::iterator it = table.begin(); it != table.end(); ++it)
    {
        std::cout << it->first << ' ' << it->second << std::endl;
    }
    return 0;
}