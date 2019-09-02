/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** IPC.hpp
*/

#ifndef CCP_PLAZZA_2018_IPC_HPP
#define CCP_PLAZZA_2018_IPC_HPP

#include <string>
#include <cstring>
#include <ostream>
#include <sys/ipc.h>
#include <sys/msg.h>

namespace plazza
{
    constexpr int SIZE_MESG = 96;

    typedef struct ipc_buff_s {
        long mesg_type;
        char mesg_text[SIZE_MESG];
    } ipc_buff_t;

    /*
     * Class for Inter Process Communication using system IPC
     * with message queues and semaphores
     */
    class IPC
    {
    public:
        IPC(int key_send, int key_rcv, const std::string &file);
        ~IPC() = default;
        void destroyQueue();
        void sendMessage(const std::string &str);
        const std::string getMessage();
        const std::string getMessageNoWait();
        const std::string getMessageTimeout(int timeout);

    private:
        int key_send;
        int key_rcv;
        std::string file;
        ipc_buff_t buffer;
        key_t key_out;
        key_t key_in;
        int msgid_out;
        int msgid_in;
    };

}

plazza::IPC &operator<<(std::string &str, plazza::IPC &ipc);
plazza::IPC &operator>>(const std::string &string, plazza::IPC &ipc);

#endif //CCP_PLAZZA_2018_IPC_HPP
