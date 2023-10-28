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

void LoggingService::add_logger(Logger&& logger)
{
    loggers[logger.id()] = std::move(logger);
}

bool LoggingService::remove_logger(std::string& logger_id)
{
    std::lock_guard<std::mutex> guard{lock_};
    if (loggers.find(logger_id) != singleton_->loggers.cend())
    {
        // return true if something is erased, else false
        return loggers.erase(logger_id) > 0;
    }
    return false;
}