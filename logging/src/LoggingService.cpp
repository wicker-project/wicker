#include "LoggingService.hpp"
#include "filter/LevelFilter.hpp"
#include <iostream>
#include <memory>

using namespace wicker;
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

bool LoggingService::add_logger(const Logger& logger)
{
    // ensure service is setup before calling
    get_instance();

    if (singleton_->loggers_.find(logger.id()) == singleton_->loggers_.cend())
    {
        singleton_->loggers_[logger.id()] = std::move(std::make_unique<Logger>(logger));
        return true;
    }
    return false;
}

bool LoggingService::remove_logger(const std::string logger_id)
{
    // ensure service is setup before calling
    get_instance();

    std::lock_guard<std::mutex> guard{lock_};
    if (singleton_->loggers_.find(logger_id) != singleton_->loggers_.cend())
    {
        // return true if something is erased, else false
        return singleton_->loggers_.erase(logger_id) > 0;
    }
    return false;
}

Logger* LoggingService::logger(const std::string logger_id)
{
    // ensure service is setup before calling
    get_instance();

    // return raw pointer to logger if found
    std::lock_guard<std::mutex> guard{lock_};
    auto res = singleton_->loggers_.find(logger_id);
    if (res != singleton_->loggers_.cend())
    {
        return res->second.get();
    }
    // else return nullptr
    return nullptr;
}