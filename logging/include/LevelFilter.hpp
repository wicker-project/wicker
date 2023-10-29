#ifndef LOGGING_LEVEL_FILTER_HPP_
#define LOGGING_LEVEL_FILTER_HPP_

#include "IFilter.hpp"
#include "utils.hpp"

namespace logging
{

enum AcceptanceType
{
    min,
    max,
    only,
    exclude
};

class LevelFilter : public IFilter
{
public:
    LevelFilter(LogLevel acceptance_level = LogLevel::all,
                AcceptanceType acceptance_type = AcceptanceType::min);

    ~LevelFilter();

    bool execute(const std::string& entry) const override
    {
        // TODO: Remove placeholder expression for LogRecord.type when that is written
        auto entry_level = LogLevel::fatal;
        auto entry_type = AcceptanceType::min;
        switch (entry_type)
        {
        case AcceptanceType::min:
            return entry_level < acceptance_level_;

        case AcceptanceType::max:
            return entry_level > acceptance_level_;

        case AcceptanceType::only:
            return entry_level == acceptance_level_;

        case AcceptanceType::exclude:
            return entry_level != acceptance_level_;
        default:
            return false;
        }
    }

private:
    /// @brief Log level acceptance threshold value
    LogLevel acceptance_level_{LogLevel::all};
    AcceptanceType type_{AcceptanceType::min};
};

} // namespace logging

#endif // LOGGING_LEVEL_FILTER_HPP_