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
    std::stringbuf buffer{};

    // create new TargetBase with copy
    TargetBase copy_target{_::test_stream};
    // load the buffer and verify data is correct
    copy_target.write(_::payload);
    copy_target.stream()->get(buffer);
    REQUIRE(buffer.str() == _::payload);

    // create new TargetBase with copy assign
    auto copy_assigned_target = TargetBase{_::test_stream};
    // reload the buffer and verify data is correct
    copy_assigned_target.write(_::payload);
    copy_assigned_target.stream()->get(buffer);
    REQUIRE(buffer.str() == _::payload);
}

/*
TEST_CASE("TargetBase: move semantics")
{}

TEST_CASE("TargetBase.stream accessors")
{}

TEST_CASE("TargetBase.write")
{}
*/