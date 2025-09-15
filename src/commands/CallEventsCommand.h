#pragma once

#include "ClientCommonCommand.h"
#include <cxxopts.hpp>

namespace mobcli::commands {

class CallEventsCommand final : public ClientCommonCommand {
public:
    CallEventsCommand();

    int execute(int argc, char* argv[]) override;
    std::string_view name() const override { return "call-events"; }
    std::string_view description() const override { return "used to send a command to specific linked device"; }

private:
    cxxopts::Options mOpts;
};

}
