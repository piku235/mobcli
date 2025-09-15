#pragma once

#include "ClientCommonCommand.h"

#include <cxxopts.hpp>

namespace mobcli::commands {

class DeviceSettingsCommand final : public ClientCommonCommand {
public:
    DeviceSettingsCommand();

    int execute(int argc, char* argv[]) override;
    std::string_view name() const override { return "device-settings"; }
    std::string_view description() const override { return "prints cosmo gtw settings"; }

private:
    cxxopts::Options mOpts;
};

}
