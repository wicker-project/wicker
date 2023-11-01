#include "TargetBase.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <sstream>

namespace _
{
std::shared_ptr<std::iostream> test_stream{};
const std::string payload{"Hello World!"};
} // namespace _

using namespace wicker;
using namespace logging;

TEST_CASE("TargetBase.write")
{
    auto terminal_target = std::make_shared<std::stringstream>();
    _::test_stream = std::static_pointer_cast<std::iostream>(terminal_target);
    TargetBase uut{_::test_stream};
    // load the terminal
    uut.write(_::payload);

    // verify data written to stream
    std::stringbuf buffer{};
    uut.stream()->get(buffer);
    REQUIRE(buffer.str() == _::payload);
}

TEST_CASE("TargetBase: copy semantics")
{
    auto terminal_target = std::make_shared<std::stringstream>();
    _::test_stream = std::static_pointer_cast<std::iostream>(terminal_target);
    // create new TargetBase with copy
    TargetBase copy_target{_::test_stream};
    // load the buffer
    copy_target.write(_::payload);
    std::stringbuf copy_buffer{};
    copy_target.stream()->get(copy_buffer);
    REQUIRE(copy_buffer.str() == _::payload);

    // create new TargetBase with copy assign
    auto copy_assigned_target = TargetBase(_::test_stream);
    // reload the buffer
    copy_assigned_target.write(_::payload);
    std::stringbuf copy_assign_buffer{};
    copy_assigned_target.stream()->get(copy_assign_buffer);
    REQUIRE(copy_assign_buffer.str() == _::payload);
}

/*
TEST_CASE("TargetBase: move semantics")
{}

TEST_CASE("TargetBase.stream accessors")
{}

TEST_CASE("TargetBase.write")
{}
*/