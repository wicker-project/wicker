#include "filter/Filterable.hpp"
#include "filter/LevelFilter.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>

using namespace wicker;
using namespace logging;

TEST_CASE("Filterable: move semantics")
{
    Filterable original{};
    Filterable move_assign{};

    original.add_filter(std::static_pointer_cast<IFilter>(
        std::make_shared<LevelFilter>(LogLevel::debug, AcceptanceType::min, "filter1")));
    original.add_filter(std::static_pointer_cast<IFilter>(
        std::make_shared<LevelFilter>(LogLevel::warn, AcceptanceType::max, "filter2")));

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
    auto filter1 = std::make_shared<LevelFilter>(LogLevel::debug, AcceptanceType::min);
    REQUIRE(uut.add_filter(std::static_pointer_cast<IFilter>(filter1)));
    REQUIRE(uut.num_filters() == 1);

    // unsuccessfully add filter of the same id
    REQUIRE_FALSE(uut.add_filter(std::static_pointer_cast<IFilter>(filter1)));
    REQUIRE(uut.num_filters() == 1);

    // successfully add another filter of the same type, but name
    auto filter2 =
        std::make_shared<LevelFilter>(LogLevel::warn, AcceptanceType::max, "warning level filter");
    REQUIRE(uut.add_filter(std::static_pointer_cast<IFilter>(filter2)));
    REQUIRE(uut.num_filters() == 2);
}

TEST_CASE("Filterable.remove_filter")
{
    Filterable uut{};

    uut.add_filter(std::static_pointer_cast<IFilter>(
        std::make_shared<LevelFilter>(LogLevel::debug, AcceptanceType::min, "filter1")));
    uut.add_filter(std::static_pointer_cast<IFilter>(
        std::make_shared<LevelFilter>(LogLevel::warn, AcceptanceType::max, "filter2")));

    // successfully remove existing filter
    REQUIRE(uut.remove_filter("filter2"));
    // unsuccessfully remove already deleted filter
    REQUIRE_FALSE(uut.remove_filter("filter2"));
}

TEST_CASE("Filterable.Clear_filters")
{
    Filterable uut{};

    uut.add_filter(std::static_pointer_cast<IFilter>(
        std::make_shared<LevelFilter>(LogLevel::debug, AcceptanceType::min, "filter1")));
    uut.add_filter(std::static_pointer_cast<IFilter>(
        std::make_shared<LevelFilter>(LogLevel::warn, AcceptanceType::max, "filter2")));

    REQUIRE(uut.num_filters() == 2);
    uut.clear_filters();
    REQUIRE(uut.num_filters() == 0);
}