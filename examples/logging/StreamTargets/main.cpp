#include "target/StreamTarget.hpp"
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const* argv[])
{
    std::stringstream target_{};
    wicker::logging::StreamTarget logStream{};
    wicker::logging::StreamTarget copyStream{};
    wicker::logging::StreamTarget moveStream{};
    logStream.write("Hello from the real world!\n");

    copyStream = logStream;
    copyStream.write("Hello from the copy world!\n");

    moveStream = std::move(logStream);
    moveStream.write("Hello from the move world!\n");
    /* code */
    return 0;
}
