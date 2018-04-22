#ifndef COM_MANAGER_H_
#define COM_MANAGER_H_

#include <deque>
#include <mutex>
#include "SerialHandler.h"

namespace cim
{
    class ComManager
    {

    public:

        ComManager(std::deque<std::string>& in_data, std::deque<std::string>& out_data);
        virtual ~ComManager();
        void init(const std::string& port, const unsigned int baud);
        bool start();
        bool stop();
        void process();
        std::mutex& get_read_lock();
        std::mutex& get_write_lock();

    private:

        SerialHandler handler_;
        std::deque<std::string>& incoming_data_;
        std::deque<std::string>& outgoing_data_;
        std::mutex read_lock_;
        std::mutex write_lock_;
    };
}

#endif /* COM_MANAGER_H_ */