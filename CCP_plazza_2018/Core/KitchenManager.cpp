/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** KitchenManager.cpp
*/

#include <algorithm>
#include "KitchenManager.hpp"
#include "Define.hpp"

/**
 * Constructor
 * @param arg
 */
plazza::KitchenManager::KitchenManager(const plazza::global::argv_t &arg): arg(arg)
{

}

/**
 * Tells all kitchens to kill themselves and wait for their response.
 */
plazza::KitchenManager::~KitchenManager()
{
    std::string message(1, macros::to_integral(global::messageTypes::KILLYOURSELF));
    for (auto &ipc : ipcs) {
        ipc.sendMessage(message);
        ipc.getMessage();
        ipc.destroyQueue();
    }
// Kitchens causes SIGABRT when deleted
//    for (int i = 0; i < kitchens.size(); ++i)
//        delete kitchens[i];
}

/**
 * Sends a command to a given kitchen
 * @param nb
 * @param command
 * @return
 */
bool plazza::KitchenManager::sendCommandTo(unsigned int nb, const std::string &command)
{
    std::string message(1, macros::to_integral(global::messageTypes::NEWCOMMAND));
    message.append(command);
    if (nb >= ipcs.size())
        return (false);
    ipcs[nb].sendMessage(message);
    std::string response = ipcs[nb].getMessage();
    return response[0] != plazza::macros::to_integral(plazza::global::messageTypes::REFUSE);
}

/**
 * Calls all kitchen to know their current load to distribute
 * @return
 */
std::vector<std::pair<int, int>> plazza::KitchenManager::getCurrentLoads()
{
    std::string message(1, macros::to_integral(global::messageTypes::LOADREPORT));
    std::vector<std::pair<int, int>> responses;
    std::string response;
    int i = 0;

    for (unsigned int u = 0; u < ipcs.size(); ++u) {
        ipcs[u].sendMessage(message);
        response = ipcs[u].getMessageTimeout(50);
        if (response[0] != macros::to_integral(plazza::global::messageTypes::SEPPUKU) && response[0] != macros::to_integral(plazza::global::messageTypes::NOTHING)) {
            responses.emplace_back(i, response[1]);
            i++;
        } else {
            removeKitchen(u);
        }
    }
    responses.erase(std::remove_if(responses.begin(), responses.end(), [this](std::pair<int, int> pair){ return pair.second <= -(static_cast<int>(arg.cooks)); }), responses.end());
    std::sort(responses.begin(), responses.end(), [](std::pair<int, int> pairA, std::pair<int, int> pairB){ return pairA.second > pairB.second; });
    return (responses);
}

/**
 * Creates a new kitchen and pairs Manager IPC with Kitchen IPC
 */
unsigned long plazza::KitchenManager::createNewKitchen()
{
    ipcs.emplace_back(key, key + 1, "/");
    kitchens.emplace_back(new plazza::kitchen::Kitchen(arg, key + 1, key));
    fwrapper.newFork(*kitchens.back());
    key += 2;
    return (ipcs.size() - 1);
}

/**
 * Deletes a given kitchen
 * TODO: Delete kitchen in vector, for now it SIGABRT due to threads
 * @param nb
 */
void plazza::KitchenManager::deleteKitchen(unsigned int nb)
{
    if (nb >= ipcs.size())
        return;
    std::string message(1, macros::to_integral(global::messageTypes::KILLYOURSELF));
    ipcs[nb].sendMessage(message);
    ipcs[nb].getMessage();
    ipcs[nb].destroyQueue();
    ipcs.erase(ipcs.begin() + nb);
//    delete kitchens[nb];
//    kitchens.erase(kitchens.begin() + nb);
}

void plazza::KitchenManager::removeKitchen(unsigned int nb)
{
    if (nb >= ipcs.size())
        return;
    ipcs[nb].destroyQueue();
    ipcs.erase(ipcs.begin() + nb);
};

void plazza::KitchenManager::checkKilled()
{
    std::vector<unsigned int> toRemove;

    for (unsigned int i = 0; i < ipcs.size(); ++i) {
        std::string response = ipcs[i].getMessageNoWait();
        if (response[0] == plazza::macros::to_integral(plazza::global::messageTypes::SEPPUKU))
            toRemove.emplace_back(i);
    }
    for (auto &removing: toRemove)
        removeKitchen(removing);
}