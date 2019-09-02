/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Serializer.hpp
*/

#ifndef CCP_PLAZZA_2018_SERIALIZER_HPP
#define CCP_PLAZZA_2018_SERIALIZER_HPP

#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <memory>

namespace plazza {
    class Serializer
    {
    public:
        template<typename T>
        static std::string serialize(const T &elem) {
            char array[sizeof(T)] = {0};
            memcpy(array, &elem, sizeof(T));
            std::string result(&array[0], &array[0] + sizeof(T));
            return (result);
        }
        template<typename T>
        static T deserialize(const std::string &elem) {
            T result;
            memcpy(&result, elem.c_str(), sizeof(T));
            return (result);
        }
    };
}

#endif //CCP_PLAZZA_2018_SERIALIZER_HPP
