/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen.hpp
*/

#ifndef CCP_PLAZZA_2018_KITCHEN_HPP
#define CCP_PLAZZA_2018_KITCHEN_HPP

#include <atomic>
#include <thread>
#include <chrono>
#include <ctgmath>
#include <ctime>
#include <csignal>
#include <unistd.h>
#include <wait.h>
#include "ThreadPool.hpp"
#include "Ingredients.hpp"
#include "IPC.hpp"
#include "Define.hpp"

namespace plazza {
    namespace kitchen {

        constexpr float timeLimitKitchen = 5.0f;

        void cook(float seconds);

        class Kitchen {

        public:
            Kitchen(const global::argv_t &arg, int ipcKey_send, int ipcKey_rcv) :
            timeMultiplier(arg.timeMult), timeStockRefill(arg.refill), nbCooks(arg.cooks),
            deathTimer(timeLimitKitchen), busy(false),
            shutdown(false), communication(ipcKey_send, ipcKey_rcv, "/") {
            }
            ~Kitchen() {
                shutdown = true;
            };

            int freeCooks() { return cookPool->freeThreads(); }
            void checkMessage();
            void checkWaiting();
            void run();
            void killMe();

        private:

            float timeMultiplier;
            float timeStockRefill;
            int nbCooks;
            double deathTimer;
            double stockTimer = 0.0;
            std::unique_ptr<threads::ThreadPool> cookPool;
            std::vector<plazza::global::command_t> waitingCommands;
            std::atomic_bool busy;
            std::atomic_bool shutdown;
            std::mutex mutex;
            std::thread chronos;
            std::thread stockThread;
            IPC communication;
            Ingredients stock;

            bool canCook(plazza::global::command_t command);
            void actualiseTimer();
            void actualiseIngredients();
            double getTimer();
        };
    }
}


#endif //CCP_PLAZZA_2018_KITCHEN_HPP
