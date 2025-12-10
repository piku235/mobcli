#pragma once

#include "ClientCommonCommand.h"

#include <jungi/mobgtw/proto/Event.pb.h>
#include <cxxopts.hpp>

namespace mobcli::commands {

class CurrentStateCommand final : public ClientCommonCommand {
public:
    CurrentStateCommand();

    int execute(int argc, char* argv[]) override;
    std::string_view name() const override { return "current-state"; }
    std::string_view description() const override { return "prints current states of linked devices"; }

private:
    cxxopts::Options mOpts;
};

}
