#include "LoggingService.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>

using namespace wicker;

namespace _
{
class MockedLoggingService : public logging::LoggingService
{
public:
    static LoggingService* wrapped_get_instance()
    {
        return get_instance();
    }
};
} // namespace _

TEST_CASE("LoggingService.get_instance")
{
    auto first = _::MockedLoggingService::wrapped_get_instance();
    auto second = _::MockedLoggingService::wrapped_get_instance();
    auto third = _::MockedLoggingService::wrapped_get_instance();

    REQUIRE(first == second);
    REQUIRE(first == third);
    REQUIRE(second == third);
}

TEST_CASE("LoggingService.add_logger")
{
    // create new logger
    auto log = logging::Logger("Log1");
    // successfully add a new logger
    REQUIRE(logging::LoggingService::add_logger(log));
    // fail to add a logger that already exists
    REQUIRE_FALSE(logging::LoggingService::add_logger(log));
}

TEST_CASE("LoggingService.remove_logger")
{
    // create new logger
    auto log = logging::Logger("Log1");
    // successfully add a new logger
    logging::LoggingService::add_logger(log);

    // successfully remove an existing logger
    REQUIRE(logging::LoggingService::remove_logger(log.id()));
    // fail to remove a non-existant logger
    REQUIRE_FALSE(logging::LoggingService::remove_logger(log.id()));
}

TEST_CASE("LoggingService.logger")
{
    // create new logger
    auto log = logging::Logger("Log1");
    // successfully add a new logger
    logging::LoggingService::add_logger(log);

    // successfully retrieve a known logger
    REQUIRE(logging::LoggingService::logger(log.id()));

    // retrieving unknown logger results in nullptr
    logging::LoggingService::remove_logger(log.id());
    REQUIRE(logging::LoggingService::logger(log.id()) == nullptr);
}