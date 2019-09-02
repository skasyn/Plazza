/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** KitchenManager.hpp
*/

#ifndef CCP_PLAZZA_2018_KITCHENMANAGER_HPP
#define CCP_PLAZZA_2018_KITCHENMANAGER_HPP

#include "ForkWrapper.hpp"
#include "IPC.hpp"
#include "Kitchen.hpp"

namespace plazza
{
    class KitchenManager
    {
    public:
        explicit KitchenManager(const global::argv_t &arg);
        ~KitchenManager();

        bool sendCommandTo(unsigned int nb, const std::string &command);
        std::vector<std::pair<int, int>> getCurrentLoads();
        unsigned long createNewKitchen();
        void deleteKitchen(unsigned int nb);
        void removeKitchen(unsigned int nb);
        void checkKilled();
    private:
        const global::argv_t arg;
        ForkWrapper<plazza::kitchen::Kitchen> fwrapper;
        std::vector<plazza::kitchen::Kitchen *> kitchens;
        std::vector<IPC> ipcs;
        int key = 0;
    };
}

#endif //CCP_PLAZZA_2018_KITCHENMANAGER_HPP
