#ifndef COMMON_THREAD_MANAGER_HPP_
#define COMMON_THREAD_MANAGER_HPP_

#include "IManager.hpp"
#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

namespace common
{
/// Private (internal namespace)
namespace
{
constexpr int default_sleep_microseconds = 1000;
}

/**
 * @brief Base class for writing specialized thread manager classes.
 */
class ThreadManagerBase : public IManager
{
public:
    /**
     * @brief Construct a new Thread Manager Base object
     */
    ThreadManagerBase();

    /**
     * @brief Construct a new Thread Manager Base object
     * @param sleep_us sleep time in microseconds
     */
    explicit ThreadManagerBase(int sleep_us);

    /**
     * @brief Copy construct a new Thread Manager Base object
     * @param to_copy Object to copy from
     * @note explicitly delete copy ctor - not wise to copy threads
     */
    ThreadManagerBase(const ThreadManagerBase& to_copy) = delete;

    /**
     * @brief Move construct a new Thread Manager Base object
     * @param to_move Object to move from
     */
    ThreadManagerBase(ThreadManagerBase&& to_move) noexcept;

    /**
     * @brief Copy assignment operator
     *
     * @param to_copy_assign object to copy assign from
     * @return ThreadManagerBase& result (LHS) of assignment
     * @note explicitly delete copy assignment operator - not wise to copy threads
     */
    ThreadManagerBase& operator=(const ThreadManagerBase& to_copy_assign) = delete;

    /**
     * @brief Move assignment operator
     *
     * @param to_move_assign object to move assign from
     * @return ThreadManagerBase& result (LHS) of assignment
     */
    ThreadManagerBase& operator=(ThreadManagerBase&& to_move_assign);

    /**
     * @brief interface method to start the managed feature.
     */
    virtual void start();

    /**
     * @brief interface method to stop the managed feature.
     * @note this is virtual, and if the derived class wished to edit it, they must ensure they call
     * this base method here to ensure proper thread teardown
     */
    virtual void stop();

    /**
     * @brief interface method to pause the managed feature.
     */
    virtual void pause();

    /**
     * @brief interface method to resume the managed feature.
     */
    virtual void resume();

    /**
     * @brief interface method returns the current managed state
     * @return ManagedState state of managed thread
     */
    ManagedState state();

    /**
     * @brief Get the sleep duration in chrono::microseconds
     * @return const std::chrono::microseconds&
     */
    virtual const std::chrono::microseconds& sleep_duration();

    /**
     * @brief Set the sleep duration
     * @param duration duration of sleep cycle in chrono::microseconds
     */
    virtual void sleep_duration(const std::chrono::microseconds& duration);

    /**
     * @brief Set the sleep duration
     * @param duration_us sleep duration as an integer in microseconds
     */
    virtual void sleep_duration(const int duration_us);

    /**
     * @brief Sleeps the managed thread for specified sleep time
     * @note Sleep can be terminated prematurely by calling stop()
     */
    virtual void sleep();

protected:
    /**
     * @brief Destroy the Thread Manager Base object
     * @note set to protected (non-virtual) to ensure called by derived class
     */
    ~ThreadManagerBase();

    /**
     * @brief Pure virtual thread execution method
     */
    virtual void execute() = 0;

    std::mutex lock_;                          ///< lock for entire manager
    ManagedState state_;                       ///< state value for manager
    std::thread process_;                      ///< execution thread for managed content
    std::chrono::microseconds sleep_duration_; ///< duration of a sleep cycle

private:
    /**
     * @brief Helper method to wrap thread execution in while loop
     * @note this is the direct means of thread execution and is the method handed to the internal
     * thread on start()
     */
    void thread_loop();

    /**
     * @brief Helper method handles the shutting down process of the managed thread
     * @note This is the direct means of thread teardown, and is leveraged by virtual stop()
     */
    void teardown_thread();

    std::condition_variable interrupt_signal_; // interrupt variable to wake from sleep
    std::mutex sleep_lock_;                    // mutex specifically for sleep interruption
};
} // namespace common

#endif // COMMON_THREAD_MANAGER_HPP_