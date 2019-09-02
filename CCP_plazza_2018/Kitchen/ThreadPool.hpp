/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** ThreadPool.hpp
*/

#ifndef CCP_PLAZZA_2018_THREADPOOL_HPP
#define CCP_PLAZZA_2018_THREADPOOL_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <thread>
#include <iostream>

namespace plazza {
    namespace threads {

        /**
         * Class ThreadPool.
         * This class implements a threadpool.
         * A threadpool handle n threads and waits for jobs to do.
         * When a job is received, it is automatically taken by the first
         * free thread.
         * When the class is destroyed, all threads are joined.
         */
        class ThreadPool {

        public:
            explicit ThreadPool (unsigned int nbr) : shutdown(false)
            {
                threads.reserve(nbr);
                for (unsigned int i = 0; i < nbr; ++i) {
                    threads.emplace_back(std::bind(&ThreadPool::entry, this,i));
                    busy.emplace_back(false);
                }
            }

            ~ThreadPool()
            {
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    shutdown = true;
                    condVar.notify_all();
                }

                for (auto &thread : threads)
                    thread.join();
            }

            /**
             *
             * @param function
             */
            void emplaceJob(std::function<void (void)> function)
            {
                std::unique_lock<std::mutex> lock(mutex);
                jobs.emplace(std::move(function));
                condVar.notify_one();
            }

            int freeThreads()
            {
                std::unique_lock<std::mutex> lock(mutex);
                int freeThreads = 0;

                for (auto const &cooking : busy) {
                    if (!cooking)
                        ++freeThreads;
                }
                return freeThreads;
            }
        private:
            void entry(int i) {
                std::function <void (void)> job;
                while (true) {
                    {
                        std::unique_lock<std::mutex> lock(mutex);
                        while (!shutdown && jobs.empty())
                            condVar.wait(lock);
                        if (jobs.empty()) {
                            return;
                        }
                        busy[i] = true;
                        job = std::move(jobs.front());
                        jobs.pop();
                    }
                    job();
                    busy[i] = false;
                }
            }
            std::mutex mutex;
            std::condition_variable condVar;
            std::atomic_bool shutdown;
            std::queue<std::function <void (void)>> jobs;
            std::vector<std::thread> threads;
            std::deque<std::atomic_bool> busy;
        };
    }
}
#endif //CCP_PLAZZA_2018_THREADPOOL_HPP
