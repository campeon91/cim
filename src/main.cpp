#include "SerialHandler.h"

int main(int argc, char const *argv[])
{
    cim::SerialHandler handler;
    handler.set_port_name("/dev/ttyUSB0");
    handler.set_baud_rate(115200);
    handler.open_port();

    while(true)
    {
        std::string data;
        if(handler.read_port(data))
        {
            std::cout << data << std::endl;
        }
    }
    return 0;
}
