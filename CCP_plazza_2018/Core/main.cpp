/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** main.cpp
*/

#include <stdlib.h>
#include "Interpretor.hpp"

int launch_plazza(char **av)
{
    plazza::global::argv_t arg;
    arg.timeMult = atof(av[1]);
    arg.cooks = atoi(av[2]);
    arg.refill = atof(av[3]) * 1000.0f;

    if (arg.timeMult == 0.0f || !arg.cooks || !arg.refill)
        return 84;

    auto interpretor = plazza::Interpretor(arg);
    interpretor.run();
    return 0;
}

void show_help()
{
    std::cout << "USAGE\n";
    std::cout << "\t./plazza m c t\n\n";
    std::cout << "DESCRIPTION\n";
    std::cout << "\tm\tMultiplier for cooking time\n";
    std::cout << "\tc\tNumber of cooks per kitchen\n";
    std::cout << "\tt\tTime to restock kitchen (in ms)\n";
}

int main(int ac, char **av)
{
    if (ac != 4) {
        show_help();
        return 84;
    }
    return (launch_plazza(av));
}