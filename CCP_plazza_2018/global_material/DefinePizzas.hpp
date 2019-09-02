/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** DefinePizzas.hpp
*/

#ifndef CCP_PLAZZA_2018_DEFINEPIZZAS_HPP
#define CCP_PLAZZA_2018_DEFINEPIZZAS_HPP

#include <vector>
#include <unordered_map>
#include "Define.hpp"

namespace plazza {
    namespace types {
        std::unordered_map<plazza::global::PizzaType, std::vector<plazza::global::ingredientsId>> ingredientMap = {
            {plazza::global::PizzaType::Margarita, {plazza::global::ingredientsId::DOUGH, plazza::global::ingredientsId::TOMATO, plazza::global::ingredientsId::GRUYERE}},
            {plazza::global::PizzaType::Regina, {plazza::global::ingredientsId::DOUGH, plazza::global::ingredientsId::TOMATO, plazza::global::ingredientsId::GRUYERE, plazza::global::ingredientsId::HAM, plazza::global::ingredientsId::MUSHROOM}},
            {plazza::global::PizzaType::Americana, {plazza::global::ingredientsId::DOUGH, plazza::global::ingredientsId::TOMATO, plazza::global::ingredientsId::GRUYERE, plazza::global::ingredientsId::STEAK}},
            {plazza::global::PizzaType::Fantasia, {plazza::global::ingredientsId::DOUGH, plazza::global::ingredientsId::TOMATO, plazza::global::ingredientsId::EGGPLANT, plazza::global::ingredientsId::GOATCHEESE, plazza::global::ingredientsId::CHIEFLOVE}}
        };
        std::unordered_map<plazza::global::PizzaType, float> timeMap = {
            {plazza::global::PizzaType::Margarita, 1.0f},
            {plazza::global::PizzaType::Regina, 2.0f},
            {plazza::global::PizzaType::Americana, 2.0f},
            {plazza::global::PizzaType::Fantasia, 4.0f}
        };

    }
}

#endif //CCP_PLAZZA_2018_DEFINEPIZZAS_HPP
