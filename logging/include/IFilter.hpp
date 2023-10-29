#ifndef LOGGING_IFILTER_HPP_
#define LOGGING_IFILTER_HPP_

#include <string>

namespace logging
{
class IFilter
{
public:
    // TODO: update this to use a LogRecord, instead of a string
    virtual bool execute(const std::string& entry) const = 0;
};

} // namespace logging

#endif // LOGGING_IFILTER_HPP_