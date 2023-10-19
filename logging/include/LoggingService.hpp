#ifndef LOGGING_LOGGING_SERVICE_HPP_
#define LOGGING_LOGGING_SERVICE_HPP_

#include <memory>
#include <mutex>

namespace logging
{
class LoggingService
{
public:
    /**
     * @brief Explicitly delete copy constructor
     * @param to_copy instance to copy from
     */
    LoggingService(const LoggingService& to_copy) = delete;

    /**
     * @brief Explicitly delete copy assignment constructor
     * @param to_copy_assign instance to copy assign from
     */
    void operator=(const LoggingService& to_copy_assign) = delete;

    /**
     * @brief Explicitly delete move constructor
     * @param to_move instance to move from
     */
    LoggingService(LoggingService&& to_move) = delete;

    /**
     * @brief Explicitly delete move assignment constructor
     * @param to_move_assign instance to move assign from
     */
    void operator=(LoggingService&& to_move_assign) = delete;

    /**
     * @brief Singleton instance allocation method
     * @return LoggingService* pointer to singleton instance
     */
    static LoggingService* get_instance();

protected:
    /**
     * @brief Construct a new Logging Service object
     */
    LoggingService() = default;

    /**
     * @brief Destroy the Logging Service object
     */
    ~LoggingService() = default;

private:
    /// pointer to singleton instance
    static LoggingService* singleton_;

    /// thread safe mutex
    static std::mutex lock_;
};
} // namespace logging

#endif // LOGGING_LOGGING_SERVICE_HPP_