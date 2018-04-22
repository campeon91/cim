#ifndef SERIAL_HANDLERSERIAL_HANDLER_H_
#define SERIAL_HANDLERSERIAL_HANDLER_H_

#include <string>
#include <unordered_map>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>


namespace cim
{
    class SerialHandler
    {

    public:

        const std::unordered_map<unsigned int, unsigned int> available_baudrates{
            {50 , B50},
            {75 , B75},
            {110 , B110},
            {134 , B134},
            {150 , B150},
            {200 , B200},
            {300 , B300},
            {600 , B600},
            {1200 , B1200},
            {1800 , B1800},
            {2400 , B2400},
            {4800 , B4800},
            {9600 , B9600},
            {19200 , B19200},
            {38400 , B38400},
            {57600 , B57600},
            {115200 , B115200},
            {230400 , B230400},
            {460800 , B460800},
            {500000 , B500000},
            {576000 , B576000},
            {921600 , B921600},
            {1000000 , B1000000},
            {1152000 , B1152000},
            {1500000 , B1500000},
            {2000000 , B2000000},
            {2500000 , B2500000},
            {3000000 , B3000000},
            {3500000 , B3500000},
            {4000000 , B4000000}
        };

        static constexpr unsigned int MAX_BUFFER_SIZE = 8192;

        SerialHandler();

        SerialHandler(SerialHandler&& handler);

        SerialHandler&& operator=(SerialHandler& other);

        auto open_port() -> bool;

        auto close_port() -> bool;

        auto read_port(std::string& data) -> bool;

        auto write_port(const std::string& payload) -> bool;

        auto get_port_name() const -> const std::string&;

        auto set_port_name(const std::string& str) -> void;

        auto get_baud_rate() const -> const unsigned int;

        void set_baud_rate(const unsigned int baud);

        virtual ~SerialHandler();

        SerialHandler(const SerialHandler& handler) = delete;

        SerialHandler& operator=(const SerialHandler& other) = delete;

    private:

        std::string port_name_;
        unsigned int baud_rate_;
        int file_descriptor_;
        struct termios settings_;
        unsigned char serial_buffer_[MAX_BUFFER_SIZE];
    };
}

#endif /* SERIAL_HANDLER_H_ */
