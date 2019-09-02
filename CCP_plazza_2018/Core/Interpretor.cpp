/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Interpretor.cpp
*/

#include "Interpretor.hpp"

bool plazza::Interpretor::run()
{
    std::string line;

    std::cout << "> ";
    while (getline(std::cin, line)) {
        try {
            interpretLine(line);
            fillCommands();
            dumpsCommands();
            for (auto const &elem : commands)
                reception.sendCommand(elem);
            commands.clear();
        } catch (const std::runtime_error &ex) {
            std::cout << ex.what() << "\n";
        }
        std::cout << "\n> ";
    }
    return true;
}

bool plazza::Interpretor::interpretLine(const std::string &line)
{
    auto commandsSplit = split(line, ';');
    for (auto const &token : commandsSplit) {
        auto command = split(token, ' ');
        command.erase(std::remove_if(command.begin(), command.end(),
            [](const std::string &str) { return str.empty(); }),
            command.end());
        if (command.size() != COMMAND_FIELDS) {
            if (command.size() < COMMAND_FIELDS)
                THROW_PLAZZA("Not enough parameters.")
            else
                THROW_PLAZZA("Too many parameters.");
        }
        for (int i = 0; i < COMMAND_FIELDS; ++i)
            checkToken(command[i], i);
        commandsSplitted.push_back(command);
    }
    return true;
}

bool plazza::Interpretor::checkToken(const std::string &word, int i)
{
    if (i == 0) {
        for (int j = 0; j < pizza_kinds; ++j) {
            if (word == pizzas[j].first)
                return true;
        }
        THROW_PLAZZA("Pizza type is not recognized.")
    } else if (i == 1) {
        if (word != "S" && word != "M" && word != "L" &&
            word != "XL" && word != "XXL")
            THROW_PLAZZA("Pizza size is not recognized.")
        return true;
    } else {
        if (std::regex_match(word, std::regex("x[0-9]*")))
            return true;
        THROW_PLAZZA("Number of pizza is incorrect (must be x[0-9]*).")
    }
}

void plazza::Interpretor::fillCommands()
{
    for (auto const &command : commandsSplitted)
        commands.push_back(getCommandFromString(command));
    commandsSplitted.clear();
}

plazza::global::command_t
plazza::Interpretor::getCommandFromString(const std::vector<std::string> &com)
{

    auto newCommand = global::command_t();

    for (int i = 0; i < COMMAND_FIELDS; ++i) {
        if (i == 0) {
            for (auto const &elem : pizzas) {
                if (elem.first == com[0])
                    newCommand.type = elem.second;
            }
        } else if (i == 1) {
            for (auto const &elem : global::pizzasSizes) {
                if (elem.first == com[1])
                    newCommand.size = elem.second;
            }
        } else
            newCommand.number = atoi(&(com[i].c_str()[1]));
    }
    return newCommand;
}

void plazza::Interpretor::dumpsCommands()
{
    for (auto const &elem : commands) {
        std::cout << "#########\n";
        std::cout << "type : " << macros::to_integral(elem.type)
            << "\n size: " << macros::to_integral(elem.size) <<
            "\nnumber : " << elem.number << "\n";
        std::cout << "#########\n\n";
    }
}

std::vector<std::string>
plazza::Interpretor::split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);

    while (std::getline(stream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}
