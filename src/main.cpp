#include "SerialHandler.h"

int main(int argc, char const *argv[])
{
    cim::SerialHandler handler;
    handler.set_port_name("/dev/ttyUSB0");
    handler.set_baud_rate(115200);
    handler.open_port();
    return 0;
}
