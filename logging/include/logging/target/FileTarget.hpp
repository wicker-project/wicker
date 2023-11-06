#ifndef LOGGING_FILE_TARGET_HPP_
#define LOGGING_FILE_TARGET_HPP_

#include "ITarget.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace wicker
{
namespace logging
{

/// @brief Enumeration to wrap over (and limit) file opening options
enum FileMode
{
    Overwrite,
    Append
};

/**
 * @brief logging target for log files
 */
class FileTarget : public ITarget
{
public:
    /**
     * @brief Construct a new FileTarget object
     */
    FileTarget() = delete;

    /**
     * @brief Construct a new File Target object
     *
     * @param filepath absolute path to output log file
     * @param mode writing mode of file. Either Overwrites, or Appends existing file.
     */
    FileTarget(const std::string& filepath, FileMode mode = FileMode::Overwrite);

    /**
     * @brief Destroy the FileTarget object
     */
    virtual ~FileTarget();

    /**
     * @brief Copy construct a new FileTarget object
     * @param to_copy object to copy from
     */
    FileTarget(const FileTarget& to_copy) = delete;

    /**
     * @brief Move construct a new FileTarget object
     * @param to_move object to move from
     */
    FileTarget(FileTarget&& to_move);

    /**
     * @brief Copy assignment operator
     * @param to_copy_assign object to copy from (rhs)
     * @return FileTarget& result of copy assignment (lhs)
     */
    FileTarget& operator=(const FileTarget& to_copy_assign) = delete;

    /**
     * @brief Move assignment operator
     * @param to_move_assign object to move from (rhs)
     * @return FileTarget& result of move assignment (lhs)
     */
    FileTarget& operator=(FileTarget&& to_move_assign);

    /**
     * @brief Accessor for path to log file
     * @return std::string absolute path to log file.
     */
    inline std::string filepath() const
    {
        return filepath_;
    }

    /**
     * @brief Accessor for file mode
     * @return FileMode writing mode of file.
     */
    inline FileMode mode() const
    {
        return mode_;
    }

    inline std::ofstream& stream()
    {
        return stream_;
    }

    /**
     * @brief Override of interface method to write data to target
     * @param payload string data to write to the stream
     */
    void write(const std::string& payload) override;

private:
    /// @brief absolute path to log file
    std::string filepath_{};
    /// @brief actual file stream instance
    std::ofstream stream_{};
    /// @brief writing mode of log file
    FileMode mode_{Overwrite};
};

} // namespace logging
} // namespace wicker

#endif // LOGGING_FILE_TARGET_HPP_