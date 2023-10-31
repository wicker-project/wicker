#include "filters/Filterable.hpp"
#include "filters/LevelFilter.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>

using namespace wicker;
using namespace logging;

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