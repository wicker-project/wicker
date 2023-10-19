#include "LoggingService.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>

namespace _
{

} // namespace _

TEST_CASE("LoggingService.get_instance")
{
    auto first = logging::LoggingService::get_instance();
    auto second = logging::LoggingService::get_instance();
    auto third = logging::LoggingService::get_instance();

    REQUIRE(first == second);
    REQUIRE(first == third);
}