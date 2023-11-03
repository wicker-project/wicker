// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#ifndef LOGGING_FILTERS_IFILTER_HPP_
#define LOGGING_FILTERS_IFILTER_HPP_

#include "../utils.hpp"
#include <string>

namespace wicker
{
namespace logging
{

/**
 * @brief Interface for logging filters, based on strategy pattern
 */
class IFilter
{
public:
    /**
     * @brief Construct a new IFilter object
     * @param name name of filter. Defaults to ""
     */
    IFilter(std::string name = "") :
        name_{name}
    {}

    /**
     * @brief Copy construct a new IFilter object
     * @param to_copy object to copy from
     */
    IFilter(const IFilter& to_copy) :
        name_{to_copy.name_}
    {}

    /**
     * @brief Move construct a new IFilter object
     * @param to_move object to move from
     */
    IFilter(IFilter&& to_move) :
        name_{std::move(to_move.name_)}
    {}

    /**
     * @brief Copy assignment operator
     *
     * @param to_copy_assign object to copy assign from (rhs)
     * @return IFilter& result of copy assignment (lhs)
     */
    IFilter& operator=(const IFilter& to_copy_assign)
    {
        name_ = to_copy_assign.name_;
        return *this;
    }

    /**
     * @brief Move assignment operator
     *
     * @param to_move_assign object to move assign from (rhs)
     * @return IFilter& result of move assignment (lhs)
     */
    IFilter& operator=(IFilter&& to_move_assign)
    {
        name_ = std::move(to_move_assign.name_);
        return *this;
    }

    /**
     * @brief Required interface method for all filters
     *
     * @param entry record to interrogate
     * @return true if strategy conditions are met, else false.
     */
    virtual bool execute(const Record& entry) const = 0;

    /**
     * @brief Accessor for filter's name
     *
     * @return std::string identification for filter
     */
    inline std::string name() const
    {
        return name_;
    }

protected:
    /// @brief Identification for filter. defaults to ""
    std::string name_{""};
};

} // namespace logging
} // namespace wicker
#endif // LOGGING_FILTERS_IFILTER_HPP_