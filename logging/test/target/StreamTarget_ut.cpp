#include "target/StreamTarget.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using namespace wicker;
using namespace logging;

namespace _
{
const std::string unterminated_test_data{"Hello tests!"};
const std::string terminated_test_data{unterminated_test_data + "\n"};
} // namespace _

TEST_CASE("StreamTarget.write: expected behaviors")
{
    // create stream and target based on stream
    std::stringstream test_stream{};
    StreamTarget uut{test_stream};

    // write unterminated data to stream and verify stream received terminated data
    uut.write(_::unterminated_test_data);
    REQUIRE(test_stream.str() == _::terminated_test_data);

    // clear stream for next test
    test_stream.str(std::string());

    // write terminated data to stream and verify stream did not receive doubly terminated data
    uut.write(_::terminated_test_data);
    REQUIRE(test_stream.str() == _::terminated_test_data);
}