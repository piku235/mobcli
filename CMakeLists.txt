cmake_minimum_required(VERSION 3.28)
project(mobcli VERSION 0.2.3)

set(CMAKE_CXX_STANDARD 17)

include(cmake/CPM.cmake)

CPMAddPackage("gh:jarro2783/cxxopts@3.3.1")
CPMAddPackage(
  URI "gh:piku235/mobilus-gtw-client@0.7.0"
  NAME mobgtw
)

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
