#include "target/FileTarget.hpp"

using namespace wicker;
using namespace logging;

FileTarget::FileTarget(const std::string& filepath, FileMode mode) :
    filepath_{filepath},
    mode_{mode}
{
    // handle user specified mode
    std::fstream::openmode open_mode{};
    switch (mode_)
    {
    case FileMode::Overwrite:
        open_mode = std::fstream::ate;
        break;

    case FileMode::Append:
        open_mode = std::fstream::trunc;
        break;

    default:
        open_mode = std::fstream::ate;
        break;
    }

    // attempt to open stream
    stream_.open(filepath_, std::fstream::out | open_mode);
}

FileTarget::~FileTarget()
{
    stream_.close();
}

FileTarget::FileTarget(FileTarget&& to_move) :
    filepath_{std::move(to_move.filepath_)},
    stream_{std::move(to_move.stream_)},
    mode_{to_move.mode_}
{}

FileTarget& FileTarget::operator=(FileTarget&& to_move_assign)
{
    filepath_ = std::move(to_move_assign.filepath_);
    stream_ = std::move(to_move_assign.stream_);
    mode_ = to_move_assign.mode_;
    return *this;
}

void FileTarget::write(const std::string& payload)
{
    // only process if valid stream
    if (!stream_.fail())
    {
        stream_.write(payload.c_str(), (long)payload.size());
    }
}