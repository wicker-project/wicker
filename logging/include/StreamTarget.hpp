#ifndef LOGGING_STREAM_TARGET_HPP_
#define LOGGING_STREAM_TARGET_HPP_

#include <iostream>
#include <memory>

namespace logging
{
class StreamTarget
{
public:
    StreamTarget() :
        stream_{nullptr}
    {}

    ~StreamTarget()
    {
        delete stream_;
    }

    friend std::ostream& operator<<(std::ostream& os, const StreamTarget& obj);

private:
    std::iostream* stream_{nullptr};
};

std::ostream& operator<<(std::ostream& os, const StreamTarget& obj)
{
    return obj.stream_ << os;
}

} // namespace logging

#endif // LOGGING_STREAM_TARGET_HPP_