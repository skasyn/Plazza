/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Exception.hpp
*/

#ifndef CCP_PLAZZA_2018_EXCEPTION_HPP
#define CCP_PLAZZA_2018_EXCEPTION_HPP

#include <stdexcept>
#include <sstream>

namespace plazza {
    class PlazzaExcept : public std::runtime_error {

    public:
        PlazzaExcept(const std::string &arg, const char *file, const char *
        function, int line) :
            std::runtime_error(arg) {
            std::ostringstream o;

            o << "\u001B[91m"<< file << ": In " << function << ":" << line <<
            ": " << arg << "\u001B[0m";
            msg = o.str();
        }

        ~PlazzaExcept() noexcept override = default;;

        const char *what() const noexcept override {
            return msg.c_str();
        }

    private:
        std::string msg;
    };
}
#endif //CCP_PLAZZA_2018_EXCEPTION_HPP
