#ifndef LOGGING_LOGGER_HPP_
#define LOGGING_LOGGER_HPP_

#include <memory>
#include <mutex>
#include <string>

namespace logging
{
/**
 * @brief Logger used to log data to specified targets
 *
 */
class Logger
{
public:
    Logger()
    {}

    Logger(std::string id) :
        id_{id}
    {}

    ~Logger() = default;

    // data accessors
    std::string id() const
    {
        return id_;
    }

    // Logging API functions

protected:
    std::string id_{""};
};

} // namespace logging

#endif // LOGGING_LOGGER_HPP_