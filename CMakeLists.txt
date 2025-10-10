cmake_minimum_required(VERSION 3.25)
project(mobcli VERSION 0.2.0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  cxxopts
  URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.3.1.zip
)
FetchContent_MakeAvailable(cxxopts)

FetchContent_Declare(
  mobgtw
  URL https://github.com/piku235/mobilus-gtw-client/archive/refs/tags/v0.4.2.zip
)
FetchContent_MakeAvailable(mobgtw)

set(MOBILUS_CA_FILE "${mobgtw_SOURCE_DIR}/certs/mobilelabs_mobilus_ca.crt")
file(READ ${MOBILUS_CA_FILE} MOBILUS_CACERT)

configure_file(
  src/mobilus_cert.h.in
  "${CMAKE_CURRENT_BINARY_DIR}/src/mobilus_cert.h"
  @ONLY
)

add_executable(mobcli
  src/main.cpp
  src/App.cpp
  src/mobilus_gtw_client/StderrLogger.cpp
  src/commands/ClientCommonCommand.cpp
  src/commands/CallEventsCommand.cpp
  src/commands/CurrentStateCommand.cpp
  src/commands/DeviceListCommand.cpp
  src/commands/DeviceSettingsCommand.cpp
  src/commands/NetworkSettingsCommand.cpp
  src/commands/SessionCommand.cpp
  src/commands/SubscribeCommand.cpp
)

target_include_directories(mobcli 
  PRIVATE
    src
    include
    ${CMAKE_CURRENT_BINARY_DIR}/src
)

target_link_libraries(mobcli
  PRIVATE
    cxxopts
    mobilus_gtw_client
)
