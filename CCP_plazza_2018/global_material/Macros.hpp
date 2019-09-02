/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Macros.hpp
*/

#ifndef CCP_PLAZZA_2018_MACROS_HPP
#define CCP_PLAZZA_2018_MACROS_HPP

#include <type_traits>
#include "Exception.hpp"

#ifdef DEBUG

template <typename U>
constexpr auto print_debug(const std::string &str, U e)
{
    printf(str.c_str(), e);
}
#else
template <typename U>
constexpr auto print_debug(const std::string &str __attribute__((unused)),
    U e __attribute__((unused)))
    {
    return;
}
#endif

#define THROW_PLAZZA(arg) throw PlazzaExcept(arg, __FILE__, __FUNCTION__, __LINE__);

namespace plazza {
    namespace macros {
        template<typename E>
        constexpr auto
        to_integral(E e) -> typename std::underlying_type<E>::type
        {
            return static_cast<typename std::underlying_type<E>::type>(e);
        }
    }
}
#endif //CCP_PLAZZA_2018_MACROS_HPP
