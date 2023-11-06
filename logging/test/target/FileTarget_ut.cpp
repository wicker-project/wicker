#include "target/FileTarget.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace wicker;
using namespace logging;

namespace _
{
const std::string log_path{"FileTarget-unit-test.log"};
const std::string unterminated_test_data{"Hello tests!"};
const std::string terminated_test_data{unterminated_test_data + "\n"};

class FileTargetFixture
{
public:
    FileTargetFixture() :
        uut_{log_path, FileMode::Overwrite}
    {}

    virtual ~FileTargetFixture() = default;
    FileTarget uut_;
};

std::string from_file()
{
    std::string res;
    std::ifstream file{log_path};
    if (file.is_open())
    {
        // get all the data from file
        while (getline(file, res))
        {
            std::cout << res << std::endl;
        }

        file.close();
        return res;
    }

    return "File failed to open properly";
}

} // namespace _

TEST_CASE_METHOD(_::FileTargetFixture, "write to local file target", "[write]")
{
    uut_.write(_::unterminated_test_data);
    uut_.stream().close();
    REQUIRE(_::from_file() == _::unterminated_test_data);
    std::remove(_::log_path.c_str());
}
