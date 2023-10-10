#include "ThreadManagerBase.hpp"
#include <catch2/catch_test_macros.hpp>
#include <chrono>
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

    virtual ~MockManager() = default;

    explicit MockManager(int sleep_us) :
        common::ThreadManagerBase(sleep_us),
        i{0}
    {}

    MockManager(const MockManager& to_copy) = delete;

    MockManager(MockManager&& to_move) noexcept :
        common::ThreadManagerBase(std::move(to_move)),
        i{to_move.i}
    {}

    MockManager& operator=(const MockManager& to_copy_assign) = delete;

    MockManager& operator=(MockManager&& to_move_assign)
    {
        common::ThreadManagerBase::operator=(std::move(to_move_assign));
        i = to_move_assign.i;
        return *this;
    }

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

TEST_CASE("ThreadManagerBase.start|stop", "[common::ThreadManagerBase]")
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
    // call stop method, verify state, and note the current count
    uut_.stop();
    REQUIRE(uut_.state() == common::ManagedState::Terminated);
    auto res = uut_.get_count();
    // wait a little while and ensure execute is no longer being called
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    REQUIRE(res == uut_.get_count());
}

TEST_CASE("ThreadManagerBase.pause|resume", "[common::ThreadManagerBase]")
{
    // create manager and start operation
    MockManager uut_{_::short_sleep};
    uut_.start();
    // call pause method, verify state, and note the execution count
    std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    uut_.pause();

    // TODO: Fix this and make it work with pipelines
    //  auto res = uut_.get_count();
    //  REQUIRE(uut_.state() == common::ManagedState::Suspended);
    //   wait a little while and ensure execute is no longer being called
    //  std::this_thread::sleep_for(std::chrono::microseconds(_::long_sleep));
    //  REQUIRE(res == uut_.get_count());
    //   call resume method, verify state, and expect higher execution count
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
    MockManager uut_{_::short_sleep};
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