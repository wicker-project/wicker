#ifndef LOGGING_FILTERS_FILTERABLE_HPP_

#define LOGGING_FILTERS_FILTERABLE_HPP_

#include "IFilter.hpp"
#include <memory>
#include <unordered_map>

namespace wicker
{
namespace logging
{
/**
 * @brief Class defining logging filter mechanics as a strategy pattern for use in any filtering
 * context
 *
 */
class Filterable
{
public:
    /**
     * @brief Construct a new Filterable object
     */
    Filterable() = default;

    /**
     * @brief Destroy the Filterable object
     */
    ~Filterable() = default;

    /**
     * @brief Copy construct a new Filterable object
     * @param to_copy object to copy from
     */
    Filterable(const Filterable& to_copy) = default;

    /**
     * @brief Construct a new Filterable object
     * @param to_move object to move from
     */
    Filterable(Filterable&& to_move) noexcept;

    /**
     * @brief Copy assign a new Filterable object
     * @param to_copy_assign object to copy assign from (rhs)
     * @return Filterable& result of copy assignment (lhs)
     */
    Filterable& operator=(const Filterable& to_copy_assign) = default;

    /**
     * @brief Move assign a new Filterable object
     * @param to_move_assign object to move assign from (rhs)
     * @return Filterable& result of move assignment (lhs)
     */
    Filterable& operator=(Filterable&& to_move_assign);

    /**
     * @brief Adds a filter to collection by its base interface (strategy pattern)
     * @param filter Filter to add to collection
     * @return true if successfully added, else false
     */
    inline bool add_filter(const std::shared_ptr<IFilter> filter)
    {
        auto res = filters_.emplace(filter->name(), filter);
        return res.second;
    }

    /**
     * @brief Get number of filters currently in collection
     * @return size_t number of filters in collection
     */
    inline size_t num_filters()
    {
        return filters_.size();
    }

    /**
     * @brief Removes filter from the collection by filter name
     *
     * @param filter_name name of filter to remove
     * @return true if filter found and removed, else false
     */
    bool remove_filter(std::string& filter_name);

    /**
     * @brief Remove all filters from collection
     */
    inline void clear_filters()
    {
        filters_.clear();
    }

protected:
    /**
     * @brief Execute strategy pattern on all filters in collection
     *
     * @param entry Record to process with filters
     * @return true if all filters are successful, else false
     */
    bool apply_filters(const Record& entry);

private:
    /// @brief collection of filters to process
    std::unordered_map<std::string, std::shared_ptr<IFilter>> filters_{};
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_FILTERS_FILTERABLE_HPP_