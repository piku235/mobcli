#pragma once

#include "Command.h"
#include "jungi/mobgtw/MqttMobilusGtwClient.h"
#include "jungi/mobgtw/io/EventLoop.h"

#include <cxxopts.hpp>
#include <filesystem/TempFile.h>
#include <memory>

namespace mobcli::commands {

class ClientCommonCommand : public Command {
protected:
    void addGeneralOptions(cxxopts::Options& opts);
    std::unique_ptr<jungi::mobgtw::logging::Logger> mqttMobilusGtwClientLogger(cxxopts::ParseResult r);
    std::unique_ptr<jungi::mobgtw::MqttMobilusGtwClient> mqttMobilusGtwClient(cxxopts::ParseResult r, jungi::mobgtw::io::EventLoop* loop = nullptr);

private:
    ::filesystem::TempFile loadMobilusCaCert();

};

}
