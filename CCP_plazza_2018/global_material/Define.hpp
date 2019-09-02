/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Pizzas.hpp
*/

#ifndef CCP_PLAZZA_2018_DEFINE_HPP
#define CCP_PLAZZA_2018_DEFINE_HPP

#include <unordered_map>
#include <Ingredients.hpp>
#include <vector>

namespace plazza {
    namespace global {

        typedef struct argv_s {
            float timeMult;
            unsigned int cooks;
            float refill;
        } argv_t;

        enum class PizzaType {
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
        };

        enum class PizzaSize {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
        };

        typedef struct command_s {
            PizzaType type;
            PizzaSize size;
            int number;
        } command_t;


        constexpr int PIZZA_TYPES = 4;

        const std::vector<std::pair<std::string, PizzaSize>> pizzasSizes = {
            {"S",   PizzaSize::S},
            {"M",   PizzaSize::M},
            {"L",   PizzaSize::L},
            {"XL",  PizzaSize::XL},
            {"XXL", PizzaSize::XXL}
        };

        enum class ingredientsId : unsigned int {
            DOUGH,
            TOMATO,
            GRUYERE,
            HAM,
            MUSHROOM,
            STEAK,
            EGGPLANT,
            GOATCHEESE,
            CHIEFLOVE
        };

        enum class messageTypes : unsigned int {
            NOTHING,
            NEWCOMMAND,
            ACCEPT,
            REFUSE,
            CURRENTLOAD,
            LOADREPORT,
            KILLYOURSELF,
            SEPPUKU
        };
    }
}
#endif //CCP_PLAZZA_2018_DEFINE_HPP
