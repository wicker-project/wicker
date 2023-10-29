#ifndef LOGGING_FILTERS_IFILTER_HPP_
#define LOGGING_FILTERS_IFILTER_HPP_

#include "utils.hpp"
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
     * @brief Required interface method for all filters
     *
     * @param entry record to interrogate
     * @return true if strategy conditions are met, else false.
     */
    virtual bool execute(const Record& entry) const = 0;
};

} // namespace logging
} // namespace wicker
#endif // LOGGING_FILTERS_IFILTER_HPP_