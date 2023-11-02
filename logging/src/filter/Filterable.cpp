#include "filter/Filterable.hpp"

using namespace wicker;
using namespace logging;

Filterable::Filterable(Filterable&& to_move) noexcept :
    filters_{std::move(to_move.filters_)}
{}

Filterable& Filterable::operator=(Filterable&& to_move_assign)
{
    filters_ = std::move(to_move_assign.filters_);
    return *this;
}

bool Filterable::remove_filter(std::string& filter_name)
{
    // remove filter if exists in collection
    if (filters_.find(filter_name) != filters_.cend())
    {
        filters_.erase(filter_name);
        return true;
    }
    return false;
}

bool Filterable::apply_filters(const Record& entry)
{
    // loop over all stored filters
    for (const auto& filter : filters_)
    {
        // break out if given filter pointer is invalid
        if (filter.second == nullptr)
        {
            return false;
        }
        // break out if filter is false
        if (!filter.second->execute(entry))
        {
            return false;
        }
    }
    // true if all filters pass (or no filters present)
    return true;
}