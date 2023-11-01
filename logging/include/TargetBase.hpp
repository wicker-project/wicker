#ifndef LOGGING_FILTERS_TARGET_BASE_HPP_
#define LOGGING_FILTERS_TARGET_BASE_HPP_

#include "ITarget.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace wicker
{
namespace logging
{

/// @brief Base class for logging targets to make writing the target stream common
class TargetBase // : public ITarget
{
public:
    /**
     * @brief Construct a new Target Base object
     */
    TargetBase() = default;

    /**
     * @brief Destroy the Target Base object
     */
    ~TargetBase() = default;

    /**
     * @brief Construct a new Target Base object with existing stream
     * @param stream shared pointer to an iostream to use as internal stream
     */
    explicit TargetBase(std::shared_ptr<std::iostream> stream);

    /**
     * @brief Copy construct a new Target Base object
     * @param to_copy object to copy from
     */
    TargetBase(const TargetBase& to_copy) = default;

    /**
     * @brief Move construct a new Target Base object
     * @param to_move object to move from
     */
    TargetBase(TargetBase&& to_move) noexcept;

    /**
     * @brief Copy assignment operator
     * @param to_copy_assign object to copy from (rhs)
     * @return TargetBase& result of copy assignment (lhs)
     */
    TargetBase& operator=(const TargetBase& to_copy_assign) = default;

    /**
     * @brief Move assignment operator
     * @param to_move_assign object to move from (rhs)
     * @return TargetBase&  result of move assignment (lhs)
     */
    TargetBase& operator=(TargetBase&& to_move_assign);

    /**
     * @brief Override of interface method to write to internal stream
     * @param payload payload data to write to the stream
     */
    void write(const std::string& payload) const;

    /**
     * @brief Get accessor for pointer to internal stream
     * @return std::shared_ptr<std::iostream> pointer to internal stream
     */
    inline std::shared_ptr<std::iostream> stream()
    {
        return stream_;
    }

    /**
     * @brief Set accessor for pointer to internal stream
     * @param stream shared pointer to stream to use as internal stream
     */
    inline void stream(std::shared_ptr<std::iostream> stream)
    {
        stream_ = stream;
    }

protected:
    /// @brief shared pointer to the target stream
    std::shared_ptr<std::iostream> stream_{nullptr};
};
} // namespace logging
} // namespace wicker

#endif // LOGGING_FILTERS_TARGET_BASE_HPP_