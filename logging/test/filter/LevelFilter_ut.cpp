#include "filter/LevelFilter.hpp"
#include <catch2/catch_test_macros.hpp>
using namespace wicker;
using namespace logging;

TEST_CASE("LevelFilter::default values")
{
    auto uut = LevelFilter{};
    // ensure default filter values are log level all, with minimum type (all inclusive)
    REQUIRE(uut.acceptance_level() == LogLevel::all);
    REQUIRE(uut.acceptance_type() == AcceptanceType::min);
    REQUIRE(uut.name() == "LevelFilter");
}

TEST_CASE("LevelFilter.execute minimum strategy")
{
    auto uut = LevelFilter{LogLevel::fatal, AcceptanceType::min};

    // create a log record
    auto entry = Record{};

    // loop thru all levels and ensure all are below "fatal"
    for (int i = (int)LogLevel::all; i < (int)LogLevel::fatal; i++)
    {
        entry.level_ = (LogLevel)i;
        REQUIRE_FALSE(uut.execute(entry));
    }

    // ensure inclusive match level matching filter minimum
    entry.level_ = LogLevel::fatal;
    REQUIRE(uut.execute(entry));
}

TEST_CASE("LevelFilter.execute maximum strategy")
{
    auto uut = LevelFilter{LogLevel::all, AcceptanceType::max};

    // create a log record
    auto entry = Record{};

    // loop thru all levels and ensure all are above "all"
    for (int i = (int)LogLevel::fatal; i > (int)LogLevel::all; i--)
    {
        entry.level_ = (LogLevel)i;
        REQUIRE_FALSE(uut.execute(entry));
    }

    // ensure inclusive match level matching filter maximum
    entry.level_ = LogLevel::all;
    REQUIRE(uut.execute(entry));
}

TEST_CASE("LevelFilter.execute only strategy")
{
    auto uut = LevelFilter{LogLevel::debug, AcceptanceType::only};
    // create a log record
    auto entry = Record{};

    // loop thru all levels
    for (int i = (int)LogLevel::all; i <= (int)LogLevel::fatal; i++)
    {
        entry.level_ = (LogLevel)i;
        // ensure successful match only when at debug level
        if (entry.level_ == LogLevel::debug)
        {
            REQUIRE(uut.execute(entry));
        }
        // ensure unsuccessful match at all other levels
        else
        {
            REQUIRE_FALSE(uut.execute(entry));
        }
    }
}

TEST_CASE("LevelFilter.execute exclude strategy")
{
    auto uut = LevelFilter{LogLevel::debug, AcceptanceType::exclude};
    // create a log record
    auto entry = Record{};

    // loop thru all levels
    for (int i = (int)LogLevel::all; i <= (int)LogLevel::fatal; i++)
    {
        entry.level_ = (LogLevel)i;
        // ensure successful match when not at debug level
        if (entry.level_ != LogLevel::debug)
        {
            REQUIRE(uut.execute(entry));
        }
        // ensure unsuccessful match at debug level
        else
        {
            REQUIRE_FALSE(uut.execute(entry));
        }
    }
}