// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#ifndef LOGGING_FILTERS_ITARGET_HPP_
#define LOGGING_FILTERS_ITARGET_HPP_

#include <string>

namespace wicker
{
namespace logging
{

/// @brief Interface abstract class for logging targets
class ITarget
{
public:
    /**
     * @brief Interface method (strategy pattern) for all targets
     *
     * @param payload string data to write to the target
     */
    virtual void write(const std::string& payload) = 0;
};
} // namespace logging
} // namespace wicker

#endif // LOGGING_FILTERS_ITARGET_HPP_