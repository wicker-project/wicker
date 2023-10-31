#ifndef LOGGING_LOGGER_HPP_
#define LOGGING_LOGGER_HPP_

#include "filters/IFilter.hpp"
#include "utils.hpp"
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace wicker
{
namespace logging
{
/**
 * @brief Logger used to log data to specified targets
 *
 */
class Logger
{
public:
    Logger() :
        id_{"root"}
    {}

    Logger(std::string id) :
        id_{id}
    {}

    ~Logger() = default;

    // Logger(const Logger& to_copy);
    // Logger(Logger&& to_move);
    // Logger& operator=(const Logger& to_copy_assign);
    // Logger& operator=(Logger&& to_move_assign);

    // data accessors
    inline std::string id() const
    {
        return id_;
    }

    // Logging API functions
    // void all(std::string&& message);
    // void trace(std::string&& message);
    // void debug(std::string&& message);
    // void info(std::string&& message);
    // void warning(std::string&& message);
    // void error(std::string&& message);
    // void fatal(std::string&& message);

protected:
    std::string id_{"root"};

private:
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_LOGGER_HPP_