#include "TargetBase.hpp"

using namespace wicker;
using namespace logging;

TargetBase::TargetBase(std::shared_ptr<std::iostream> stream) :
    stream_{stream}
{}

TargetBase::TargetBase(TargetBase&& to_move) noexcept :
    stream_{std::move(to_move.stream_)}
{}

TargetBase& TargetBase::operator=(TargetBase&& to_move_assign)
{
    to_move_assign.stream_ = std::move(to_move_assign.stream_);
    return *this;
}

void TargetBase::write(const std::string& payload) const
{
    if (stream_ != nullptr)
    {
        *stream_ << payload;
    }
}
