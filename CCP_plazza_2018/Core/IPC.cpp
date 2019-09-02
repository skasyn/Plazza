/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** IPC.cpp
*/

#include <iostream>
#include <unistd.h>
#include <thread>
#include "Define.hpp"
#include "IPC.hpp"
#include "Macros.hpp"

/*
 * Constructor create the ipc message queue
 * File is used to create key
 * Key_nb is a unique identifier to generate a queue in the file key
 */
plazza::IPC::IPC(int key_send, int key_rcv, const std::string &file) : key_send(key_send), key_rcv(key_rcv), file(file)
{
    key_out = ftok(file.c_str(), key_send);
    key_in = ftok(file.c_str(), key_rcv);
    msgid_out = msgget(key_out, 0777 | IPC_CREAT);
    msgid_in = msgget(key_in, 0777 | IPC_CREAT);
    if (key_out == -1 || key_in == -1 || msgid_out == -1 || msgid_in == -1)
        THROW_PLAZZA("IPC Creation Failed.");
}

/*
 * Destroys message queues
 * Is not in destructor because destructor may be called unintentionally by std::vector operations
 */
void plazza::IPC::destroyQueue()
{
    msgctl(msgid_in, IPC_RMID, nullptr);
    msgctl(msgid_out, IPC_RMID, nullptr);
}

/*
 * Sends message to the message queue
 */
void plazza::IPC::sendMessage(const std::string &str)
{
    for (char &i : buffer.mesg_text)
        i = '\0';
    memcpy(buffer.mesg_text, str.c_str(), str.size());
    buffer.mesg_type = 1;
    msgsnd(msgid_out, &buffer, sizeof(buffer), 0);
}

/*
 * Recovers one message in the message queue
 */
const std::string plazza::IPC::getMessage()
{
    for (char &i : buffer.mesg_text)
        i = '\0';
    buffer.mesg_type = 0;
    msgrcv(msgid_in, &buffer, sizeof(buffer), 1, 0);
    return std::string(buffer.mesg_text, SIZE_MESG);
}

const std::string plazza::IPC::getMessageNoWait()
{
    for (char &i : buffer.mesg_text)
        i = '\0';
    buffer.mesg_type = 0;
    msgrcv(msgid_in, &buffer, sizeof(buffer), 1, IPC_NOWAIT);
    return std::string(buffer.mesg_text, SIZE_MESG);
}

const std::string plazza::IPC::getMessageTimeout(int timeout)
{
    std::string response;
    for (int i = timeout; i > 0; i -= 10) {
        response = getMessageNoWait();
        if (response[0] != plazza::macros::to_integral(plazza::global::messageTypes::NOTHING))
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return response;
}

/*
 * << operator overload to recover a message
 */
plazza::IPC &operator<<(std::string &str, plazza::IPC &ipc)
{
    str = ipc.getMessage();
    return ipc;
}

/*
 * >> operator overload to send a message
 */
plazza::IPC &operator>>(const std::string &string, plazza::IPC &ipc)
{
    ipc.sendMessage(string);
    return ipc;
}
