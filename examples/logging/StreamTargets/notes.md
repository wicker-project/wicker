# Overview
This example demonstrates how to use a wicker::logging::StreamTarget. This class is intended to be used within the confines of a logger, and not ever really directly by a user. If you ever intend to create a new logger type outside of what is provided in Wicker, this will be of use.

# StreamTarget uses
A stream target is used when the target of a log should be a stream like std::cout, or some other user internal stream. StreamTarget inherits from ITarget, for the sole purpose of pointer casting for containerization. As more targets are added, the only way they can be containerized is to do so from some common base class. Wicker tends to lean on base class pointer based type obfuscation to do this, and here is an example. Since we are using the ITarget interface, we must use the write method contained within it to actually push data onto the stream. An example can be seen below:

```c++
#include "wicker/logging/target/StreamTarget.hpp"
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char const* argv[])
{
    //uses std::cout by default
    wicker::logging::StreamTarget log_stream{};
    
    //push message onto the stream
    log_stream.write("Hello from a logging stream target!\n");

    //specify a local stream target, and write data there
    std::stringstream local_stream{};
    wicker::logging::StreamTarget log_local_target{local_stream};
    log_local_target.write("Writes data into local_stream, and not to cout.\n");

    return 0;
}

```

One key thing to note here, is that the write method is dummy simple. It is not doing any data checking, or termination appending. The reasoning here is because these are features that are covered by loggers, and not targets. The targets should only be handling the basics of taking some string data and putting it in the write location. This decision was made because it provides the most separation between logging logic concerns, and OS dependent features like files, and console streams. 

And as a final parting comment, I want to point out that the include path here is a bit ugly. Once again, the reasoning here is this isn't really intended to be used directly, but instead internal to the logging system. 