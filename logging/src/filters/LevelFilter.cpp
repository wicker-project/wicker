#include "LevelFilter.hpp"

using namespace wicker;
using namespace logging;

LevelFilter::LevelFilter(LogLevel acceptance_level, AcceptanceType acceptance_type) :
    acceptance_level_{acceptance_level},
    acceptance_type_{acceptance_type}
{}

LevelFilter::LevelFilter(const LevelFilter& to_copy) :
    acceptance_level_{to_copy.acceptance_level_},
    acceptance_type_{to_copy.acceptance_type_}
{}

LevelFilter::LevelFilter(LevelFilter&& to_move) :
    acceptance_level_{to_move.acceptance_level_},
    acceptance_type_{to_move.acceptance_type_}
{}

LevelFilter& LevelFilter::operator=(const LevelFilter& to_copy_assign)
{
    acceptance_level_ = to_copy_assign.acceptance_level_;
    acceptance_type_ = to_copy_assign.acceptance_type_;
    return *this;
}

LevelFilter& LevelFilter::operator=(LevelFilter&& to_move_assign)
{
    acceptance_level_ = to_move_assign.acceptance_level_;
    acceptance_type_ = to_move_assign.acceptance_type_;
    return *this;
}

bool LevelFilter::execute(const Record& entry) const
{
    // switch on stored type and make comparison appropriately
    switch (acceptance_type_)
    {
    case AcceptanceType::min:
        // only accept levels at or above minimum level
        return entry.level_ >= acceptance_level_;

    case AcceptanceType::max:
        // only accept levels at or below maximum level
        return entry.level_ <= acceptance_level_;

    case AcceptanceType::only:
        // only accept level at specified value
        return entry.level_ == acceptance_level_;

    case AcceptanceType::exclude:
        // only accept levels not at specified value
        return entry.level_ != acceptance_level_;

    default:
        return false;
    }
}
