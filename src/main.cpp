#include "ComManager.h"
#include "SerialHandler.h"

int main(int argc, char const* argv[]) {
  std::deque<std::string> incoming_data;
  std::deque<std::string> outgoing_data;
  pulsar::ComManager manager(incoming_data, outgoing_data);
  manager.init("/dev/ttyUSB0", 115200);
  manager.start();
  std::thread manager_thread{manager.spawn()};
  manager_thread.join();
  return 0;
}
