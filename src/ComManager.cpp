#include "ComManager.h"
#include <chrono>


namespace cim
{
    ComManager::ComManager( std::deque<std::string>& in_data, std::deque<std::string>& out_data)
    : handler_(), incoming_data_(in_data), outgoing_data_(out_data)
    , read_lock_(), write_lock_()
    {
    }

    ComManager::~ComManager()
    {
        stop();
    }

    auto ComManager::init(const std::string& port, const unsigned int baud) -> void
    {
        handler_.set_port_name(port);
        handler_.set_baud_rate(baud);
    }

    auto ComManager::start() -> bool
    {
        return handler_.open_port();
    }

    auto ComManager::stop() -> bool
    {
        return handler_.close_port();
    }

    auto ComManager::process() -> void
    {
        while(true)
        {
            write_lock_.lock();
            if(!outgoing_data_.empty())
            {
                handler_.write_port(outgoing_data_.back());
                outgoing_data_.pop_back();
            }
            write_lock_.unlock();

            std::string data;
            if(handler_.read_port(data))
            {
                read_lock_.lock();
                incoming_data_.push_front(data);
                read_lock_.unlock();
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }

    auto ComManager::spawn() -> std::thread
    {
        return std::thread{[&] {process();}};
    }

    auto ComManager::get_read_lock() -> std::mutex&
    {
        return read_lock_;
    }

    auto ComManager::get_write_lock() -> std::mutex&
    {
        return write_lock_;
    }
}
