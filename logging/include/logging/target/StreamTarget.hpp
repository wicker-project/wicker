#ifndef LOGGING_TARGET_STREAM_TARGET_HPP_
#define LOGGING_TARGET_STREAM_TARGET_HPP_

//#include "TargetBase.hpp"
#include "filter/Filterable.hpp"
#include "target/ITarget.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace wicker
{
namespace logging
{

class StreamTarget : public ITarget, Filterable
{
public:
    StreamTarget() :
        stream_{nullptr}
    {}

    ~StreamTarget() = default;

    explicit StreamTarget(std::ostream& stream) :
        stream_{&stream}
    {}

    void write(std::string& payload) override
    {
        *stream_ << payload;
    }

private:
    std::ostream* stream_{nullptr};
};

} // namespace logging

} // namespace wicker

#endif // LOGGING_TARGET_STREAM_TARGET_HPP_