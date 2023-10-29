#ifndef LOGGING_RECORD_HPP_
#define LOGGING_RECORD_HPP_

#include <chrono>
#include <string>

namespace logging
{
enum LogLevel
{
    invalid = -1,
    all,
    trace,
    debug,
    info,
    warn,
    error,
    fatal
};

std::string log_level(const LogLevel value)
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
};

} // namespace logging

#endif // LOGGING_RECORD_HPP_