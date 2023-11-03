// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#include "LevelFilter.hpp"

using namespace wicker;
using namespace logging;

LevelFilter::LevelFilter(LogLevel acceptance_level,
                         AcceptanceType acceptance_type,
                         std::string name) :
    IFilter(name),
    acceptance_level_{acceptance_level},
    acceptance_type_{acceptance_type}
{}

LevelFilter::LevelFilter(const LevelFilter& to_copy) = default;

LevelFilter::LevelFilter(LevelFilter&& to_move) noexcept :
    IFilter(to_move),
    acceptance_level_{to_move.acceptance_level_},
    acceptance_type_{to_move.acceptance_type_}
{}

LevelFilter& LevelFilter::operator=(const LevelFilter& to_copy_assign) = default;

LevelFilter& LevelFilter::operator=(LevelFilter&& to_move_assign)
{
    acceptance_level_ = to_move_assign.acceptance_level_;
    acceptance_type_ = to_move_assign.acceptance_type_;
    IFilter::operator=(std::move(to_move_assign));
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
