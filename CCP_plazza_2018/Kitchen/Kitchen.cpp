/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen.cpp
*/

#include "Serializer.hpp"
#include "Kitchen.hpp"
#include "Macros.hpp"
#include "DefinePizzas.hpp"

/**
 * TODO: Report to the reception of the pizza being done
 * @param seconds
 */
void plazza::kitchen::cook(float seconds)
{
    auto milli = static_cast<int>(round(seconds * 1000.0));
    std::this_thread::sleep_for(std::chrono::milliseconds(milli));
    std::cout << "Finished cooking !\n";
}

void plazza::kitchen::Kitchen::actualiseTimer()
{
    while (true) {
        auto begin_t = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (shutdown)
            return;
        bool value = false;
        {
            std::unique_lock<std::mutex> lock(mutex);
            if (freeCooks() != nbCooks)
                value = true;

            if (value) {
                deathTimer = timeLimitKitchen;
            } else {
                auto end_t = std::chrono::high_resolution_clock::now();
                double timeElapsed = std::chrono::duration<double, std::milli>(end_t - begin_t).count() / 1000.0;

                if (timeElapsed < 0.0 || timeElapsed > 1.0)
                    timeElapsed = 0;
                deathTimer -= timeElapsed;
            }
        }
    }
}

/**
 * TODO: Change sleep_for time
 */
void plazza::kitchen::Kitchen::actualiseIngredients()
{
    while (true) {
        auto begin_t = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (shutdown)
            return;
        {
            std::unique_lock<std::mutex> lock(mutex);

            auto end_t = std::chrono::high_resolution_clock::now();
            double timeElapsed = std::chrono::duration<double, std::milli>(end_t - begin_t).count() / 1000.0;
            if (timeElapsed < 0 || timeElapsed > 1)
                timeElapsed = 0;
            stockTimer += timeElapsed * 1000.0;
            if (stockTimer >= timeStockRefill) {
                stockTimer = 0;
                stock.refillStock();
            }
        }
    }
}

/**
 * @return
 */
double plazza::kitchen::Kitchen::getTimer()
{
    std::unique_lock<std::mutex> lock(mutex);
    return deathTimer;
}

bool plazza::kitchen::Kitchen::canCook(plazza::global::command_t command)
{
    if (plazza::types::ingredientMap.find(command.type) == plazza::types::ingredientMap.end() ||
    plazza::types::timeMap.find(command.type) == plazza::types::timeMap.end())
        return false;
    if (!freeCooks() && waitingCommands.size() >= static_cast<unsigned int>(nbCooks))
        return false;
    auto ingredients = plazza::types::ingredientMap[command.type];
    for (auto ingredient : ingredients) {
        if (!stock.getStockValue(static_cast<unsigned int>(plazza::macros::to_integral(ingredient))))
            return false;
    }
    if (freeCooks()) {
        for (auto ingredient : ingredients)
            stock.takeIngredient(static_cast<unsigned int>(plazza::macros::to_integral(ingredient)));
        cookPool->emplaceJob(std::bind(plazza::kitchen::cook, plazza::types::timeMap[command.type] * timeMultiplier));
    } else {
        waitingCommands.emplace_back(command);
    }
    return true;
}

/**
 * Get message from IPC and do things accordingly
 */
void plazza::kitchen::Kitchen::checkMessage()
{
    std::string message = communication.getMessageNoWait();
    if (message[0] == macros::to_integral(global::messageTypes::NOTHING))
        return;
    if (message[0] == macros::to_integral(global::messageTypes::KILLYOURSELF))
        killMe();
    if (message[0] == macros::to_integral(global::messageTypes::NEWCOMMAND)) {
        message.erase(message.begin());
        plazza::global::command_t command = plazza::Serializer::deserialize<plazza::global::command_t>(message);
        if (!canCook(command))
            communication.sendMessage(std::string(1, macros::to_integral(global::messageTypes::REFUSE)));
        else
            communication.sendMessage(std::string(1, macros::to_integral(global::messageTypes::ACCEPT)));
    }
    if (message[0] == macros::to_integral(global::messageTypes::LOADREPORT)) {
        std::string messageReport(1, macros::to_integral(global::messageTypes::CURRENTLOAD));
        messageReport += static_cast<char>(freeCooks());
        communication.sendMessage(messageReport);
    }
}

void plazza::kitchen::Kitchen::checkWaiting()
{
    for (auto size = waitingCommands.size(); size > 0; --size) {
        auto command = waitingCommands[0];
        waitingCommands.erase(waitingCommands.begin());
        if (!canCook(command))
            waitingCommands.emplace_back(command);
    }
}

/**
 * Main loop for kitchen called by the ForkWrapper
 */
void plazza::kitchen::Kitchen::run()
{
    cookPool = std::make_unique<plazza::threads::ThreadPool>(nbCooks);
    chronos = std::thread(&Kitchen::actualiseTimer, this);
    stockThread = std::thread(&Kitchen::actualiseIngredients, this);
    while (getTimer() >= 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        checkWaiting();
        checkMessage();
    }
    killMe();
}

void plazza::kitchen::Kitchen::killMe()
{
    print_debug("Killing ... %d\n", getpid());
    communication.sendMessage(std::string(1, macros::to_integral(global::messageTypes::SEPPUKU)));
    auto pid = getpid();
    kill(pid, SIGTERM);
    bool died = false;

    for (int loop = 0; !died && loop < 5; ++loop)
    {
        int status;
        sleep(1);
        if (waitpid(pid, &status, WNOHANG) == pid)
            died = true;
    }
    if (!died)
        kill(pid, SIGKILL);
}
