#ifndef LOGGING_UTILS_HPP_
#define LOGGING_UTILS_HPP_

#include <chrono>
#include <string>

namespace wicker
{
namespace logging
{
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

static std::string log_level(const LogLevel value)
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

struct Record
{
    std::chrono::system_clock::time_point timestamp_{std::chrono::system_clock::now()};
    LogLevel level_{LogLevel::all};
    std::string message_{""};
    std::string logger_id_{""};
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_UTILS_HPP_