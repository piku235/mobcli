#pragma once

#include <jungi/mobgtw/logging/Logger.h>

namespace mobcli::mobgtw {

class StderrLogger final : public jungi::mobgtw::logging::Logger {
public:
    void info(const std::string& message) override { }
    void error(const std::string& message) override;
};

}
