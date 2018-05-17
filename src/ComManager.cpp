#include "ComManager.h"
#include <chrono>

namespace pulsar {
ComManager::ComManager(std::deque<std::string>& in_data,
                       std::deque<std::string>& out_data)
    : handler_(),
      incoming_data_(in_data),
      outgoing_data_(out_data),
      read_lock_(),
      write_lock_() {}

ComManager::~ComManager() {
  stop();
}

void ComManager::init(const std::string& port, const unsigned int baud) {
  handler_.set_port_name(port);
  handler_.set_baud_rate(baud);
}

bool ComManager::start() {
  return handler_.open_port();
}

bool ComManager::stop() {
  return handler_.close_port();
}

void ComManager::process() {
  while (true) {
    write_lock_.lock();
    if (!outgoing_data_.empty()) {
      handler_.write_port(outgoing_data_.back());
      outgoing_data_.pop_back();
    }
    write_lock_.unlock();

    std::string data;
    if (handler_.read_port(data)) {
      read_lock_.lock();
      incoming_data_.push_front(data);
      read_lock_.unlock();
    } else {
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }
}

std::thread ComManager::spawn() {
  return std::thread{[&] { process(); }};
}

std::mutex& ComManager::get_read_lock() {
  return read_lock_;
}

std::mutex& ComManager::get_write_lock() {
  return write_lock_;
}
}  // namespace pulsar
