#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>


int main(int argc, char const *argv[])
{
    plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);
    LOG_DEBUG << "Hello cim";
    return 0;
}