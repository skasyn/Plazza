/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Ingredients.hpp
*/

#ifndef CCP_PLAZZA_2018_INGREDIENTS_HPP
#define CCP_PLAZZA_2018_INGREDIENTS_HPP

#include <mutex>

namespace plazza {
    namespace kitchen {

        constexpr int initStock = 5;
        constexpr int ingredientsMax = 9;

        class Ingredients {

        public:
            Ingredients() {
                for (int &ingredient : ingredients)
                    ingredient = initStock;
            }
            ~Ingredients() = default;

            unsigned int getStockValue(unsigned int id) {
                std::unique_lock<std::mutex> lock(mutex);
                if (id > ingredientsMax)
                    return 0;
                return ingredients[id];
            }

            void takeIngredient(unsigned int id) {
                std::unique_lock<std::mutex> lock(mutex);
                if (id > ingredientsMax)
                    return;
                --ingredients[id];
            }

            void refillStock(void) {
                std::unique_lock<std::mutex> lock(mutex);
                for (int &ingredient : ingredients)
                    ++ingredient;
            }

        private:
            int ingredients[ingredientsMax];
            std::mutex mutex;
        };
    }
}

#endif //CCP_PLAZZA_2018_INGREDIENTS_HPP
