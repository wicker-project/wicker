// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#include "ThreadManagerBase.hpp"
using namespace common;

ThreadManagerBase::ThreadManagerBase() :
    state_{ManagedState::Uninitialized},
    sleep_duration_{std::chrono::microseconds(::default_sleep_microseconds)},
    interrupt_signal_{}
{}

ThreadManagerBase::ThreadManagerBase(int sleep_duration_us) :
    state_{ManagedState::Uninitialized},
    sleep_duration_{std::chrono::microseconds(sleep_duration_us)},
    interrupt_signal_{}
{}

ThreadManagerBase::ThreadManagerBase(std::chrono::microseconds sleep_duration) :
    state_{ManagedState::Uninitialized},
    sleep_duration_{sleep_duration},
    interrupt_signal_{}
{}

ThreadManagerBase::ThreadManagerBase(ThreadManagerBase&& to_move) noexcept :
    state_{std::move(to_move.state_)},
    sleep_duration_{std::move(to_move.sleep_duration_)},
    interrupt_signal_{}
{}

ThreadManagerBase& ThreadManagerBase::operator=(ThreadManagerBase&& to_move_assign)
{
    state_ = std::move(to_move_assign.state_);
    sleep_duration_ = std::move(to_move_assign.sleep_duration_);
    return *this;
}

ThreadManagerBase::~ThreadManagerBase()
{
    teardown_thread();
}

void ThreadManagerBase::start()
{
    std::lock_guard<std::mutex> guard{lock_};
    if (state_ == ManagedState::Uninitialized)
    {
        state_ = ManagedState::Running;
        process_ = std::thread(&ThreadManagerBase::thread_loop, this);
    }
}

void ThreadManagerBase::stop()
{
    teardown_thread();
}

void ThreadManagerBase::pause()
{
    std::lock_guard<std::mutex> guard{lock_};
    if (state_ == ManagedState::Running)
    {
        state_ = ManagedState::Suspended;
    }
}

void ThreadManagerBase::resume()
{
    std::lock_guard<std::mutex> guard{lock_};
    if (state_ == ManagedState::Suspended)
    {
        state_ = ManagedState::Running;
    }
}

ManagedState ThreadManagerBase::state()
{
    std::lock_guard<std::mutex> guard{lock_};
    return state_;
}

const std::chrono::microseconds& ThreadManagerBase::sleep_duration()
{
    std::lock_guard<std::mutex> guard{lock_};
    return sleep_duration_;
}

void ThreadManagerBase::sleep_duration(const std::chrono::microseconds& duration)
{
    std::lock_guard<std::mutex> guard{lock_};
    sleep_duration_ = duration;
}

void ThreadManagerBase::sleep_duration(const int duration_us)
{
    std::lock_guard<std::mutex> guard{lock_};
    sleep_duration_ = std::chrono::microseconds(duration_us);
}

void ThreadManagerBase::sleep()
{
    if (state() == ManagedState::Running)
    {
        std::unique_lock<std::mutex> sleep_guard{sleep_lock_};
        interrupt_signal_.wait_for(sleep_guard, sleep_duration_);
    }
}

void ThreadManagerBase::thread_loop()
{
    // terminate thread loop upon state set to end or fault
    while (state_ != ManagedState::Fault && state_ != ManagedState::Terminated)
    {
        // only execute thread logic if set to running
        if (state_ == ManagedState::Running)
        {
            execute();
        }
    }
}

void ThreadManagerBase::teardown_thread()
{
    std::lock_guard<std::mutex> guard{lock_};
    if (state_ == ManagedState::Running || state_ == ManagedState::Suspended)
    {
        state_ = ManagedState::Terminated;
        interrupt_signal_.notify_one();
        process_.join();
    }
}