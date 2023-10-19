#include "LoggingService.hpp"
#include <iostream>

using namespace logging;

// definition of static object instances
LoggingService* LoggingService::singleton_{nullptr};
std::mutex LoggingService::lock_;

LoggingService* LoggingService::get_instance()
{
    std::lock_guard<std::mutex> guard{lock_};
    if (singleton_ == nullptr)
    {
        singleton_ = new LoggingService{};
    }
    return singleton_;
}