#ifndef LOGGING_FILTERS_FILTERABLE_HPP_
#define LOGGING_FILTERS_FILTERABLE_HPP_

#include "IFilter.hpp"
#include <memory>
#include <vector>

namespace wicker
{
namespace logging
{

class Filterable
{
public:
    /**
     * @brief Adds a filter to the logger by its base interface (strategy pattern)
     * @param filter Filter to add to logger
     */
    inline void add_filter(std::IFilter&& filter)
    {
        filters_.push_back(std::move(filter));
    }

    inline void clear_filters()
    {
        filters_.clear();
    }

protected:
    bool apply_filters(const Record& entry)
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

private:
    std::vector<std::shared_ptr<IFilter>> filters_{};
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_FILTERS_FILTERABLE_HPP_