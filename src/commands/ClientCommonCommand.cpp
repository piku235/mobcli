#include "mobilus_cert.h"
#include "ClientCommonCommand.h"
#include "Utils.h"
#include "mobgtw/StderrLogger.h"
#include "jungi/mobgtw/MqttDsn.h"
#include "jungi/mobgtw/proto/DeviceSettingsRequest.pb.h"

#include <iostream>

using namespace mobcli::mobgtw;
using namespace jungi::mobgtw;
using filesystem::TempFile;

static constexpr size_t kMobilusMqttPort = 8883;

static void printRawMessage(const Envelope& envelope)
{
    using namespace mobcli::Utils;

    std::cout << "client_id: " << bin2hex(envelope.clientId) << std::endl
              << "message_size: " << envelope.size() << std::endl
              << "message_type: " << static_cast<int>(envelope.messageType) << std::endl
              << "message_body_length: " << envelope.messageBody.size() << std::endl
              << "response_status: " << static_cast<int>(envelope.responseStatus) << std::endl
              << "timestamp: " << envelope.timestamp << std::endl
              << std::endl;
}

namespace mobcli::commands {

void ClientCommonCommand::addGeneralOptions(cxxopts::Options& opts)
{
    // clang-format off
    opts.add_options("General", {
        {"h,host", "mobilus hostname/IP", cxxopts::value<std::string>()->default_value(Utils::getEnvOr("MOBILUS_HOST", "mobilus"))},
        {"u,username", "mobilus username/login", cxxopts::value<std::string>()->default_value(Utils::getEnvOr("MOBILUS_USERNAME", "admin"))},
        {"p,password", "mobilus password", cxxopts::value<std::string>()->default_value(Utils::getEnvOr("MOBILUS_PASSWORD", "admin"))},
        {"v,verbose", "prints extra logs", cxxopts::value<bool>()->default_value("false")},
        {"help", "prints help"}
    });
    // clang-format on
}

std::unique_ptr<MqttMobilusGtwClient> ClientCommonCommand::mqttMobilusGtwClient(cxxopts::ParseResult r, io::EventLoop* loop)
{
    static auto mobilusCaCertFile = loadMobilusCaCert();
    static StderrLogger logger;

    auto builder = MqttMobilusGtwClient::builder();

    builder
        .dsn({ true, std::nullopt, std::nullopt, r["host"].as<std::string>(), ::kMobilusMqttPort, mobilusCaCertFile.path(), false })
        .login({ r["username"].as<std::string>(), r["password"].as<std::string>() })
        .useKeepAliveMessage(std::make_unique<proto::DeviceSettingsRequest>())
        .useLogger(&logger);

    if (nullptr != loop) {
        builder.attachTo(loop);
    }

    if (r.count("verbose")) {
        builder.onRawMessage(printRawMessage);
    }

    return builder.build();
}

TempFile ClientCommonCommand::loadMobilusCaCert()
{
    auto cacert = TempFile::unique("/tmp/mobilus_ca_XXXXXX");
    cacert.write(kMobilusCaCert, sizeof(kMobilusCaCert));

    return cacert;
}

}
