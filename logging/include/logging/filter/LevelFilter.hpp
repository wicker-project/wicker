// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#ifndef LOGGING_LEVEL_FILTER_HPP_
#define LOGGING_LEVEL_FILTER_HPP_

#include "IFilter.hpp"
#include "utils.hpp"

namespace wicker
{
namespace logging
{

/**
 * @brief types of level acceptance for level filtering
 */
enum AcceptanceType
{
    min,
    max,
    only,
    exclude
};

/**
 * @brief Filter to log records based on log level.
 */
class LevelFilter : public IFilter
{
public:
    /**
     * @brief Construct a new Level Filter object
     * @param acceptance_level log level to base acceptance strategy off of. Defaults to
     * LogLevel::all.
     * @param acceptance_type  acceptance strategy. Defaults to AcceptanceType::min.
     * @param name name of filter. Defaults to "LevelFilter"
     */
    LevelFilter(LogLevel acceptance_level = LogLevel::all,
                AcceptanceType acceptance_type = AcceptanceType::min,
                std::string name = "LevelFilter");

    /**
     * @brief Destroy the Level Filter object
     */
    ~LevelFilter() = default;

    /**
     * @brief Copy construct a new Level Filter object
     * @param to_copy LevelFilter to copy from
     */
    LevelFilter(const LevelFilter& to_copy);

    /**
     * @brief Move construct a new Level Filter object
     * @param to_move LevelFilter to move from
     */
    LevelFilter(LevelFilter&& to_move) noexcept;

    /**
     * @brief Copy assignment operator
     * @param to_copy_assign (rhs) to copy assign from
     * @return LevelFilter& result of copy assignment (lhs)
     */
    LevelFilter& operator=(const LevelFilter& to_copy_assign);

    /**
     * @brief Move assignment operator
     * @param to_move_assign (rhs) to move assign from
     * @return LevelFilter&& result of move assignment (lhs)
     */
    LevelFilter& operator=(LevelFilter&& to_move_assign);

    /**
     * @brief Required strategy method. filter determined by log level of entry
     *
     * @param entry Record to verify for admittance
     * @return true if entry's log level is compatable with the predefined comparison strategy, else
     * false
     */
    bool execute(const Record& entry) const;

    /**
     * @brief accessor for internal acceptance level
     * @return LogLevel of filter
     */
    inline LogLevel acceptance_level()
    {
        return acceptance_level_;
    }

    /**
     * @brief accessor for internal acceptance type
     * @return AcceptanceType of filter
     */
    inline AcceptanceType acceptance_type()
    {
        return acceptance_type_;
    }

private:
    /// @brief Log level acceptance threshold value
    LogLevel acceptance_level_{LogLevel::all};
    /// @brief Type of acceptance criteria
    AcceptanceType acceptance_type_{AcceptanceType::min};
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_LEVEL_FILTER_HPP_