#include "ThreadManagerBase.hpp"
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

namespace _
{
constexpr int short_sleep = 500;
constexpr int long_sleep = 1000;
constexpr int really_long_sleep = 5000;
} // namespace _

class MockManager : public common::ThreadManagerBase
{
public:
    MockManager() :
        common::ThreadManagerBase(),
        i{0}
    {}

    MockManager(int sleep_us) :
        common::ThreadManagerBase(sleep_us),
        i{0}
    {}

    void execute() override
    {
        // extra scope around logic to not lock while sleeping
        {
            std::lock_guard<std::mutex> guard{lock_};
            i++;
        }
        this->sleep();
    }

    int get_count()
    {
        std::lock_guard<std::mutex> guard{lock_};
        return i;
    }

private:
    int i;
};

TEST_CASE("ThreadManagerBase.start", "[common::ThreadManagerBase]")
{
    // create manager and ensure starting state is correct
    MockManager uut_{_::short_sleep};
    REQUIRE(uut_.state() == common::ManagedState::Uninitialized);
    // call start method and ensure state change is reflected
    uut_.start();
    REQUIRE(uut_.state() == common::ManagedState::Running);
    // wait a little and ensure that the execute method is being called
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    REQUIRE(uut_.get_count() > 0);
    // tear down thread manager - required for thread to join and close
    uut_.stop();
}

TEST_CASE("ThreadManagerBase.stop", "[common::ThreadManagerBase]")
{
    // Create manager and start operation
    MockManager uut_{_::short_sleep};
    uut_.start();
    // call stop method, verify state, and note the current count
    uut_.stop();
    REQUIRE(uut_.state() == common::ManagedState::Terminated);
    auto res = uut_.get_count();
    // wait a little while and ensure execute is no longer being called
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    REQUIRE(res == uut_.get_count());
}

TEST_CASE("ThreadManagerBase.pause", "[common::ThreadManagerBase]")
{
    // create manager and start operation
    MockManager uut_{_::short_sleep};
    uut_.start();
    // call pause method, verify state, and note the execution count
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    uut_.pause();
    REQUIRE(uut_.state() == common::ManagedState::Suspended);
    auto res = uut_.get_count();
    // wait a little while and ensure execute is no longer being called
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    REQUIRE(res == uut_.get_count());
    // tear down thread manager - required for thread to join and close
    uut_.stop();
}

TEST_CASE("ThreadManagerBase.resume", "[common::ThreadManagerBase]")
{
    // create manager and start operation
    auto uut_ = MockManager{_::short_sleep};
    uut_.start();
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    // call pause method, verify state, and note the execution count
    uut_.pause();
    auto res = uut_.get_count();
    uut_.resume();
    REQUIRE(uut_.state() == common::ManagedState::Running);
    // wait a little while and ensure execute has been called once again
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    REQUIRE(res < uut_.get_count());
    // tear down thread manager - required for thread to join and close
    uut_.stop();
}

TEST_CASE("ThreadManagerBase.sleep_duration", "[common::ThreadManagerBase]")
{
    auto uut_ = MockManager{_::short_sleep};
    // verify the initial value from construction is interpreted correctly
    REQUIRE(uut_.sleep_duration() == std::chrono::microseconds(_::short_sleep));
    // set to new microsecond value
    auto set_micro = std::chrono::microseconds(_::short_sleep);
    uut_.sleep_duration(set_micro);
    REQUIRE(uut_.sleep_duration() == set_micro);
    // set to new int value
    uut_.sleep_duration(_::really_long_sleep);
    REQUIRE(uut_.sleep_duration() == std::chrono::microseconds(_::really_long_sleep));
    // tear down thread manager - required for thread to join and close
    uut_.stop();
}