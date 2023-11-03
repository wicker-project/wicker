// SPDX-FileCopyrightText: © 2023 The Wicker Project
// SPDX-License-Identifier: Modified MIT

#include "target/StreamTarget.hpp"

using namespace wicker;
using namespace logging;

StreamTarget::StreamTarget() :
    stream_{nullptr}
{}

StreamTarget::StreamTarget(std::ostream& stream) :
    stream_{&stream}
{}

StreamTarget::StreamTarget(const StreamTarget& to_copy) :
    stream_{to_copy.stream_}
{}

StreamTarget::StreamTarget(StreamTarget&& to_move) noexcept :
    stream_{to_move.stream_}
{}

StreamTarget& StreamTarget::operator=(const StreamTarget& to_copy_assign)
{
    stream_ = to_copy_assign.stream_;
    return *this;
}

StreamTarget& StreamTarget::operator=(StreamTarget&& to_move_assign)
{
    stream_ = to_move_assign.stream_;
    return *this;
}

void StreamTarget::write(const std::string& payload)
{
    // only process if valid stream
    if (stream_ != nullptr)
    {
        // insert payload into stream
        *stream_ << payload;
    }
}