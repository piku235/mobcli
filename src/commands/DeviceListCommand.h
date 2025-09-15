#pragma once

#include "ClientCommonCommand.h"

#include <cxxopts.hpp>
#include <google/protobuf/repeated_field.h>

namespace mobcli::commands {

class DeviceListCommand final : public ClientCommonCommand {
public:
    DeviceListCommand();

    int execute(int argc, char* argv[]) override;
    std::string_view name() const override { return "device-list"; }
    std::string_view description() const override { return "lists linked devices"; }

private:
    cxxopts::Options mOpts;

    template <typename T>
    std::string formatList(const google::protobuf::RepeatedField<T>& repeatedField);
};

}
