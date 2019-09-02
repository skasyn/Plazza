/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception.cpp
*/

#include <algorithm>
#include "Reception.hpp"
#include "Serializer.hpp"

plazza::Reception::Reception(const global::argv_t &arg) :
timeMultiplier(arg.timeMult), cooksPerKitchen(arg.cooks),
timeStockRefill(arg.refill), time(Clock::now()), manager(arg), args(arg)
{
    std::cout << "Welcome to the Wallito e Forchetta !\nHow can I serve you ?\n";
    print_debug("Values : timemult : %f ", timeMultiplier);
    print_debug("cooks : %d ", cooksPerKitchen);
    print_debug("refill: %d\n", timeStockRefill);
}

plazza::Reception::~Reception()
{
    std::cout << "Thank you for coming, have a nica day !\n";
}

void plazza::Reception::sendCommand(const plazza::global::command_t &command)
{
    manager.checkKilled();
    auto loads = manager.getCurrentLoads();

    if (loads.empty()) {
        manager.createNewKitchen();
        loads = manager.getCurrentLoads();
    }
    std::string sendingString = plazza::Serializer::serialize<plazza::global::command_t>(command);
    for (int nb = command.number; nb > 0; --nb) {
        while (!loads.empty() && !manager.sendCommandTo(static_cast<unsigned int>(loads[0].first), sendingString)) {
            loads.erase(loads.begin());
        }
        if (loads.empty()) {
            auto index = manager.createNewKitchen();
            manager.sendCommandTo(static_cast<unsigned int>(index), sendingString);
            loads.emplace_back(index, cooksPerKitchen - 1);
            std::sort(loads.begin(), loads.end(), [](std::pair<int, int> pairA, std::pair<int, int> pairB){ return pairA.second > pairB.second; });
        } else {
            loads[0].second--;
            loads.erase(std::remove_if(loads.begin(), loads.end(), [this](std::pair<int, int> pair){ return pair.second <= -(static_cast<int>(cooksPerKitchen)); }), loads.end());
            std::sort(loads.begin(), loads.end(), [](std::pair<int, int> pairA, std::pair<int, int> pairB){ return pairA.second > pairB.second; });
        }
    }
}
