#pragma once

#include "ClientCommonCommand.h"

#include <cxxopts.hpp>

namespace jungi::mobgtw::proto {
class CallEvents;
}

namespace mobcli::commands {

class SubscribeCommand final : public ClientCommonCommand {
public:
    SubscribeCommand();

    int execute(int argc, char* argv[]) override;
    std::string_view name() const override { return "sub"; }
    std::string_view description() const override { return "subscribes to all device events"; }

private:
    cxxopts::Options mOpts;

    static void printCallEvents(const jungi::mobgtw::proto::CallEvents& callEvents);
};

}
