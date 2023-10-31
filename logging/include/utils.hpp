#ifndef LOGGING_UTILS_HPP_
#define LOGGING_UTILS_HPP_

#include <chrono>
#include <string>

namespace wicker
{
namespace logging
{

/// @brief Enumeration for all log level definition and order
enum LogLevel
{
    all,
    trace,
    debug,
    info,
    warn,
    error,
    fatal
};

/**
 * @brief Static method to generate a formatted string from LogLevel value
 *
 * @param value LogLevel value to get formatted string for
 * @return std::string formatted string matching log level
 */
static std::string log_level_string(const LogLevel value)
{
    switch (value)
    {
    case LogLevel::all:
        return "All";
        break;
    case LogLevel::trace:
        return "Trace";
        break;
    case LogLevel::debug:
        return "Debug";
        break;
    case LogLevel::info:
        return "Info";
        break;
    case LogLevel::warn:
        return "Warning";
        break;
    case LogLevel::error:
        return "Error";
        break;
    case LogLevel::fatal:
        return "Fatal";
        break;
    default:
        return "Invalid";
        break;
    }
}

/**
 * @brief Structure defining a singular log entry record.
 */
struct Record
{
    /// @brief timestamp at the moment of creation for the record
    std::chrono::system_clock::time_point timestamp_{std::chrono::system_clock::now()};
    /// @brief LogLevel for the record
    LogLevel level_{LogLevel::all};
    /// @brief User's message for the record
    std::string message_{""};
    /// @brief Id of the logger that generated this record
    std::string logger_id_{""};
    /// @brief String detailing time format
    std::string time_format{""};
    /// @brief String detailing entire record format
    std::string record_format{""};
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_UTILS_HPP_