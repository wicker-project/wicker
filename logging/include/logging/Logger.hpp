// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#ifndef LOGGING_LOGGER_HPP_
#define LOGGING_LOGGER_HPP_

#include "filter/Filterable.hpp"
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
class Logger : public Filterable
{
public:
    /**
     * @brief Construct a new Logger object
     *
     */
    Logger() :
        id_{"root"}
    {}

    /**
     * @brief Construct a new Logger object
     *
     * @param id identification string for logger
     */
    Logger(std::string id) :
        id_{id}
    {}

    /**
     * @brief Destroy the Logger object
     *
     */
    ~Logger() = default;

    // Logger(const Logger& to_copy);
    // Logger(Logger&& to_move);
    // Logger& operator=(const Logger& to_copy_assign);
    // Logger& operator=(Logger&& to_move_assign);

    // data accessors
    /**
     * @brief retrieve the logger's id.
     *
     * @return std::string identification string for logger
     */
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
    /// @brief logger's identification
    std::string id_{"root"};
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_LOGGER_HPP_