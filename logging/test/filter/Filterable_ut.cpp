#include "filter/Filterable.hpp"
#include "filter/LevelFilter.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>

using namespace wicker;
using namespace logging;

/// @brief Mocked filterable to expose apply_filters for testing
class MockFilterable : public Filterable
{
public:
    bool apply_filters(const Record& entry)
    {
        return Filterable::apply_filters(entry);
    }
};

TEST_CASE("Filterable: move semantics")
{
    Filterable original{};
    Filterable move_assign{};
    original.add_filter(LevelFilter{LogLevel::debug, AcceptanceType::min, "filter1"});
    original.add_filter(LevelFilter{LogLevel::debug, AcceptanceType::max, "filter2"});

    Filterable move{std::move(original)};
    REQUIRE(move.num_filters() == 2);

    move_assign = std::move(move);
    REQUIRE(move_assign.num_filters() == 2);
}

TEST_CASE("Filterable.add_filter")
{
    Filterable uut{};
    REQUIRE(uut.num_filters() == 0);

    // successfully add a filter
    REQUIRE(uut.add_filter(LevelFilter{LogLevel::debug, AcceptanceType::min}));
    REQUIRE(uut.num_filters() == 1);

    // unsuccessfully add filter of the same id
    REQUIRE_FALSE(uut.add_filter(LevelFilter{LogLevel::debug, AcceptanceType::min}));
    REQUIRE(uut.num_filters() == 1);

    // successfully add another filter of the same type, but name
    auto filter2 = LevelFilter{LogLevel::warn, AcceptanceType::max, "warning level filter"};
    REQUIRE(uut.add_filter(filter2));
    REQUIRE(uut.num_filters() == 2);
}

TEST_CASE("Filterable.remove_filter")
{
    Filterable uut{};

    uut.add_filter(LevelFilter{LogLevel::debug, AcceptanceType::min, "filter1"});
    uut.add_filter(LevelFilter{LogLevel::warn, AcceptanceType::max, "filter2"});

    // successfully remove existing filter
    REQUIRE(uut.remove_filter("filter2"));
    // unsuccessfully remove already deleted filter
    REQUIRE_FALSE(uut.remove_filter("filter2"));
}

TEST_CASE("Filterable.Clear_filters")
{
    Filterable uut{};

    uut.add_filter(LevelFilter{LogLevel::debug, AcceptanceType::min, "filter1"});
    uut.add_filter(LevelFilter{LogLevel::warn, AcceptanceType::max, "filter2"});

    REQUIRE(uut.num_filters() == 2);
    uut.clear_filters();
    REQUIRE(uut.num_filters() == 0);
}

TEST_CASE("Filterable.apply_filters")
{
    MockFilterable uut{};

    // adding these two filters create a band-pass of log levels debug, info and warn
    uut.add_filter(LevelFilter{LogLevel::debug, AcceptanceType::min, "filter1"});
    uut.add_filter(LevelFilter{LogLevel::warn, AcceptanceType::max, "filter2"});

    // create placeholder record
    auto entry = Record{};
    entry.logger_id_ = "test logger";
    entry.message_ = "Hello test!";

    // loop thru all levels
    for (int i = (int)LogLevel::all; i <= (int)LogLevel::fatal; i++)
    {
        // apply level to record
        entry.level_ = (LogLevel)i;

        // ensure three allowable entries pass
        if (entry.level_ == LogLevel::debug || entry.level_ == LogLevel::info ||
            entry.level_ == LogLevel::warn)
        {
            REQUIRE(uut.apply_filters(entry));
        }
        // ensure all other entires fail
        else
        {
            REQUIRE_FALSE(uut.apply_filters(entry));
        }
    }
}