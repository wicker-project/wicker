#include "target/StreamTarget.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
    wicker::logging::StreamTarget logStream{std::cout};
    logStream.write("Hello from the real world!");
    /* code */
    return 0;
}
