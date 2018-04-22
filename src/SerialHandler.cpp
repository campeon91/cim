#include "SerialHandler.h"


namespace cim
{

    SerialHandler::SerialHandler(): port_name_(""), baud_rate_(0)
    {}

    SerialHandler::~SerialHandler()
    {
        close_port();
    }

    SerialHandler::SerialHandler(SerialHandler&& other)
    {
        port_name_ = other.get_port_name();
        baud_rate_ = other.get_baud_rate();
        other.set_port_name("");
        other.set_baud_rate(0);
    }

    SerialHandler&& SerialHandler::operator=(SerialHandler& other)
    {
        return std::move(other);
    }

    auto SerialHandler::open_port() -> bool
    {
        file_descriptor_ = open(port_name_.c_str(), O_RDWR | O_NDELAY | O_NOCTTY);
        if (file_descriptor_ == -1)
        {
            std::cerr << "\033[1;31mError: \033[0m" << " unable to open " << port_name_ << std::endl;
            return false;
        }
        else
        {
            fcntl(file_descriptor_, F_SETFL, 0);
        }

        tcgetattr(file_descriptor_, &settings_);

        if (cfsetispeed(&settings_, available_baudrates.at(baud_rate_)) ||
            cfsetospeed(&settings_, available_baudrates.at(baud_rate_)))
        {
            std::cerr << "\033[1;31mError: \033[0m" << " unable to set baudrate for " << port_name_ << std::endl;
            return false;
        }

        settings_.c_cflag |= (CLOCAL | CREAD);
        settings_.c_cflag &= ~CSIZE;
        settings_.c_cflag |= CS8;
        settings_.c_cflag &= ~PARENB;
        settings_.c_cflag &= ~CSTOPB;
        settings_.c_cflag &= ~CSIZE;
        settings_.c_cflag |= CS8;
        settings_.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        settings_.c_oflag &= ~OPOST;
        if (tcsetattr(file_descriptor_, TCSANOW, &settings_))
        {
            std::cerr << "\033[1;31mError: \033[0m" << " unable to configure " << port_name_ << std::endl;
        }
        return true;
    }

    auto SerialHandler::close_port() -> bool
    {
        return (!close(file_descriptor_));
    }

    auto SerialHandler::read_port(std::string& data) -> bool
    {
        const int res = read(file_descriptor_, serial_buffer_, sizeof(serial_buffer_));

        if(res > 0)
        {
            data = std::move(std::string(serial_buffer_, serial_buffer_ + res));
            return true;
        }
        if(res < 0)
        {
            std::cerr << "\033[1;31mError: \033[0m" << " unable to read from " << port_name_ << std::endl;
        }
        return false;
    }

    auto SerialHandler::write_port(const std::string& payload) -> bool
    {
        if (payload.empty())
        {
            return false;
        }

        const ssize_t res = write(file_descriptor_, payload.c_str(), payload.size());

        if(res <= 0)
        {
            std::cerr << "Nothing was written " << std::endl;
            return false;
        }
        return true;
    }

    auto SerialHandler::get_port_name() const -> const std::string&
    {
        return port_name_;
    }

    auto SerialHandler::set_port_name(const std::string& str) -> void
    {
        port_name_ = str;
    }

    auto SerialHandler::get_baud_rate() const -> const unsigned int
    {
        return baud_rate_;
    }

    auto SerialHandler::set_baud_rate(const unsigned int baud) -> void
    {
        auto elem = std::find_if(
            available_baudrates.begin(),
            available_baudrates.end(),
            [baud](auto elem){return elem.first == baud;});

        if(available_baudrates.end() == elem)
        {
            std::cerr << "\033[1;31mError: \033[0m" << "Baudrate " << baud << " is not supported." << std::endl;
            baud_rate_ = 0;
        }
        else
        {
            baud_rate_ = baud;
        }
    }
}
