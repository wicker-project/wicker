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

TEST_CASE("StreamTarget.write: stringstream target")
{
    // create stream and target based on stream
    std::stringstream test_stream{};
    StreamTarget uut{test_stream};

    // write unterminated data to stream and verify stream received unterminated data
    uut.write(_::unterminated_test_data);
    REQUIRE(test_stream.str() == _::unterminated_test_data);

    // clear stream for next test
    test_stream.str(std::string());

    // write terminated data to stream and verify stream received terminated data
    uut.write(_::terminated_test_data);
    REQUIRE(test_stream.str() == _::terminated_test_data);
}

TEST_CASE("StreamTarget.write: cout target")
{
    StreamTarget uut{}; // defaults to std::cout

    // swap std::cout buffer for local test buffer - catch clobbers cout
    auto original_cout_buffer = std::cout.rdbuf();
    std::ostringstream test_buffer;
    std::cout.rdbuf(test_buffer.rdbuf());

    // write unterminated data to cout
    uut.write(_::unterminated_test_data);

    // switch std::cout buffer back for catch's use
    std::cout.rdbuf(original_cout_buffer);
    // verify test buffer was filled properly
    REQUIRE(test_buffer.str() == _::unterminated_test_data);
}

TEST_CASE("StreamTarget: copy semantics")
{
    // create stream and target based on stream
    std::stringstream test_stream{};
    StreamTarget original{test_stream};
    StreamTarget copy_assign{};

    // create copy with constructor
    StreamTarget copy{original};
    // write to copy and verify test_stream has data
    copy.write(_::terminated_test_data);
    REQUIRE(test_stream.str() == _::terminated_test_data);

    // clear stream
    test_stream.str(std::string{});

    // create copy with assignment
    copy_assign = original;
    // write to copy assignment and verify test_stream has data;
    copy_assign.write(_::unterminated_test_data);
    REQUIRE(test_stream.str() == _::unterminated_test_data);
}

TEST_CASE("StreamTarget: move semantics")
{
    // create stream and target based on stream
    std::stringstream test_stream{};
    StreamTarget original{test_stream};
    StreamTarget move_assign{};

    // create move with constructor
    StreamTarget move{std::move(original)};
    // write to move and verify test_stream has data
    move.write(_::terminated_test_data);
    REQUIRE(test_stream.str() == _::terminated_test_data);

    // clear stream
    test_stream.str(std::string{});

    // create copy with assignment
    move_assign = std::move(move);
    // write to copy assignment and verify test_stream has data;
    move_assign.write(_::unterminated_test_data);
    REQUIRE(test_stream.str() == _::unterminated_test_data);
}