#include "Filterable.hpp"

using namespace wicker;
using namespace logging;

bool Filterable::apply_filters(const Record& entry)
{
    // loop over all stored filters
    for (const auto& filter : filters_)
    {
        // break out if given filter pointer is invalid
        if (filter == nullptr)
        {
            return false;
        }
        // break out if filter is false
        if (!filter->execute(entry))
        {
            return false;
        }
    }
    // true if all filters pass (or no filters present)
    return true;
}