/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** ForkWrapper.hpp
*/

#ifndef CCP_PLAZZA_2018_FORKWRAPPER_HPP
#define CCP_PLAZZA_2018_FORKWRAPPER_HPP

#include <unistd.h>
#include <csignal>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include "Macros.hpp"

namespace plazza
{
    template <typename T>
    class ForkWrapper
    {
        public:
            ~ForkWrapper() = default;

            /**
             * Creates a new process and calls given class in that new fork
             * @param elem
             */
            void newFork(T &elem) {
                int pid = fork();

                if (pid == 0) {
                    try {
                        /*TODO: Change to run or std::function or whatever*/
                        elem.run();
                        exit(0);
                    } catch (const std::runtime_error &ex) {
                        std::cout << ex.what() << "\n";
                    }
                } else if (pid > 0) {
                    pidList.push_back(pid);
                } else {
                    THROW_PLAZZA("Fork failed.")
                }
            }
        private:
            std::vector<int> pidList;
    };
}

#endif //CCP_PLAZZA_2018_FORKWRAPPER_HPP
