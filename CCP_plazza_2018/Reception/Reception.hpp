/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception.hpp
*/

#ifndef CCP_PLAZZA_2018_RECEPTION_HPP
#define CCP_PLAZZA_2018_RECEPTION_HPP

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "Macros.hpp"
#include "Define.hpp"
#include "IPC.hpp"
#include "Ingredients.hpp"
#include "KitchenManager.hpp"

namespace plazza {

    using Clock = std::chrono::high_resolution_clock;

    class Reception {

    public:
        explicit Reception(const global::argv_t &arg);
        ~Reception();

        void sendCommand(const global::command_t &);

    private:

        float timeMultiplier;
        unsigned cooksPerKitchen;
        float timeStockRefill;
        Clock::time_point time;
        std::vector<IPC> ipcs;
        plazza::KitchenManager manager;
        global::argv_t args;
    };
}


#endif //CCP_PLAZZA_2018_RECEPTION_HPP
