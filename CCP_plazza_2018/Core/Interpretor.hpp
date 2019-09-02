/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Interpretor.hpp
*/

#ifndef CCP_PLAZZA_2018_INTERPRETOR_HPP
#define CCP_PLAZZA_2018_INTERPRETOR_HPP

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <Macros.hpp>
#include "Define.hpp"
#include "Define.hpp"
#include "Reception.hpp"

namespace plazza {

    constexpr int COMMAND_FIELDS = 3;

    class Interpretor {

    public:
        explicit Interpretor(const global::argv_t &arg) : reception(arg) {}

        ~Interpretor() = default;

        std::vector<global::command_t> getCommands() {
            return commands;
        }

        bool run();

    private:

        // Reception
        Reception reception;

        // Holds the parsed commands
        std::vector<global::command_t> commands;

        // Holds parsed input
        std::vector<std::vector<std::string>> commandsSplitted;

        /*
         * Holds a list of available pizzas.
         * TODO : change enum into something else in order to dynamically add pizzas
         */
        std::vector<std::pair<std::string, global::PizzaType>> pizzas = { //
            {"regina",    global::PizzaType::Regina},
            {"margarita", global::PizzaType::Margarita},
            {"americana", global::PizzaType::Americana},
            {"fantasia",  global::PizzaType::Fantasia}
        };

        // Nbr of available pizzas (useless because of pizzas.size() ?)
        int pizza_kinds = global::PIZZA_TYPES;

        /*
         * Split the getline() into commands, then commands into tokens while
         * checking if there was no input error.
         */
        bool interpretLine(const std::string &line);

        /*
         * Check one of the three possible type of data input.
         */
        bool checkToken(const std::string &word, int i);

        /*
         * Fills the commands var with parsed input.
         */
        void fillCommands();

        /*
         * Creates a command_t element from a valid std::string
         */
        global::command_t getCommandFromString(const std::vector<std::string> &com);

        /*
         * Dumps the commands var. Used in debugging.
         */
        void dumpsCommands();

        /*
         * Classic string.split()
         */
        static std::vector<std::string>
        split(const std::string &s, char delimiter);
    };
}
#endif //CCP_PLAZZA_2018_INTERPRETOR_HPP
