#ifndef COM_MANAGER_H_
#define COM_MANAGER_H_

#include <deque>
#include <thread>
#include <mutex>
#include "SerialHandler.h"

namespace cim
{
    class ComManager
    {

    public:

        ComManager(std::deque<std::string>& in_data, std::deque<std::string>& out_data);

        virtual ~ComManager();

        auto init(const std::string& port, const unsigned int baud) -> void;

        auto start() -> bool;

        auto stop() -> bool;

        auto process() -> void;

        auto spawn() -> std::thread;

        auto get_read_lock() -> std::mutex&;

        auto get_write_lock() -> std::mutex&;

    private:

        SerialHandler handler_;
        std::deque<std::string>& incoming_data_;
        std::deque<std::string>& outgoing_data_;
        std::mutex read_lock_;
        std::mutex write_lock_;
    };
}

#endif /* COM_MANAGER_H_ */