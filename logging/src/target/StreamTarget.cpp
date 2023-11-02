#include "target/StreamTarget.hpp"

using namespace wicker;
using namespace logging;

StreamTarget::StreamTarget() :
    stream_{nullptr},
    terminator_{"\n"}
{}

StreamTarget::StreamTarget(std::ostream& stream, const std::string& terminator) :
    stream_{&stream},
    terminator_{terminator}
{}

StreamTarget::StreamTarget(const StreamTarget& to_copy) :
    stream_{to_copy.stream_},
    terminator_{to_copy.terminator_}
{}

StreamTarget::StreamTarget(StreamTarget&& to_move) noexcept :
    stream_{to_move.stream_},
    terminator_{std::move(to_move.terminator_)}
{}

StreamTarget& StreamTarget::operator=(const StreamTarget& to_copy_assign)
{
    stream_ = to_copy_assign.stream_;
    terminator_ = to_copy_assign.terminator_;
    return *this;
}

StreamTarget& StreamTarget::operator=(StreamTarget&& to_move_assign)
{
    stream_ = to_move_assign.stream_;
    terminator_ = to_move_assign.terminator_;
    return *this;
}

void StreamTarget::write(const std::string& payload)
{
    // only process if valid stream
    if (stream_ != nullptr)
    {
        // insert payload into stream
        *stream_ << payload;

        // insert terminator if not present
        if (payload.find_last_of(terminator_) == std::string::npos)
        {
            *stream_ << terminator_;
        }
    }
}