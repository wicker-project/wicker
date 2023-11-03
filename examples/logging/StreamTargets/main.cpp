#include "target/StreamTarget.hpp"
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const* argv[])
{
    // uses std::cout by default
    wicker::logging::StreamTarget log_stream{};

    // push message onto the stream
    log_stream.write("Hello from a logging stream target!\n");

    // specify a local stream target, and write data there
    std::stringstream local_stream{};
    wicker::logging::StreamTarget log_local_target{local_stream};
    log_local_target.write("Writes data into local_stream, and not to cout.\n");

    return 0;
}