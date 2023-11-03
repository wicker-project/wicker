// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#ifndef LOGGING_TARGET_STREAM_TARGET_HPP_
#define LOGGING_TARGET_STREAM_TARGET_HPP_

//#include "TargetBase.hpp"
#include "ITarget.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace wicker
{
namespace logging
{

/**
 * @brief Logging target for streams such as std::cout and std::err
 *
 */
class StreamTarget : public ITarget
{
public:
    /**
     * @brief Construct a new Stream Target object
     */
    StreamTarget();

    /**
     * @brief Destroy the Stream Target object
     */
    ~StreamTarget() = default;

    /**
     * @brief Construct a new Stream Target object
     * @param stream target stream reference
     */
    explicit StreamTarget(std::ostream& stream);

    /**
     * @brief Copy construct a new Stream Target object
     * @param to_copy object to copy from
     */
    StreamTarget(const StreamTarget& to_copy);

    /**
     * @brief Move construct a new Stream Target object
     * @param to_move object to move from
     */
    StreamTarget(StreamTarget&& to_move) noexcept;

    /**
     * @brief Copy assignment operator
     * @param to_copy_assign object to copy from (rhs)
     * @return StreamTarget& result of copy assignment (lhs)
     */
    StreamTarget& operator=(const StreamTarget& to_copy_assign);

    /**
     * @brief Move assignment operator
     * @param to_move_assign object to move from (rhs)
     * @return StreamTarget& result of move assignment (lhs)
     */
    StreamTarget& operator=(StreamTarget&& to_move_assign);

    /**
     * @brief override of required interface method to write data to target
     * @param payload string data to write to the stream
     */
    void write(const std::string& payload) override;

private:
    /// @brief pointer to the target stream
    std::ostream* stream_{nullptr};
};

} // namespace logging

} // namespace wicker

#endif // LOGGING_TARGET_STREAM_TARGET_HPP_